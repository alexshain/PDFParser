#include "PDFParser.h"
#include "Composite/ReportComposite.h"
#include "Composite/SettingsDataTable.h"
#include "ParsingStrategy/ParsingOrdinaryTable.h"
#include "ParsingStrategy/ParsingNestedTable.h"

#include <iostream>
#include <algorithm>

PDFParser::PDFParser(const std::string& filename) : filename_(filename) {
    aReport_ = std::make_unique<AnsysReport>();
    setDocument();
}

std::unique_ptr<AnsysReport> PDFParser::parse() {
    std::vector<PoDoFo::PdfTextEntry> globalEntries;

    for(int i = 0; i < document_.GetPages().GetCount(); i++) {
        std::vector<PoDoFo::PdfTextEntry> entries;
    
        PdfTextExtractParams params;
        params.Flags = PdfTextExtractFlags::TokenizeWords;
        PdfPage& page = document_.GetPages().GetPageAt(i);
        page.ExtractTextTo(entries, params);

        int factor = document_.GetPages().GetCount() - i;
        for(auto& entry : entries) {
            entry.Y += page.GetMediaBox().Height * factor;
            globalEntries.push_back(entry);
        }
    }

    std::sort(globalEntries.begin(), globalEntries.end(), 
                [](PdfTextEntry& a, PdfTextEntry& b) {
                    if(a.Y != b.Y)
                        return a.Y > b.Y;
                    return a.X < b.X;
                });

    
    fillReport(globalEntries);
    return std::move(aReport_);
}

void PDFParser::reset(const std::string& filename) {
    filename_ = filename;
    setDocument();
}

void PDFParser::setDocument() {
    try {
        document_.Load(filename_);
    } catch (PdfError& e) {
        std::cerr << "Error reading PDF: " << e.what() << std::endl;
    }
}

bool checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) {
    double maxSpaceLength = (currEntry.Length / currEntry.Text.size()) * 18; //это для nested tables'
    double spaceLength = currEntry.X - prevEntry.X - prevEntry.Length;
    return spaceLength < maxSpaceLength;
}

void setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) {
    line = entries[index].Text;
    index++;
    while(checkComponentOfSentence(entries[index - 1], entries[index]) && entries[index - 1].Y == entries[index].Y) {
        line.append(" " + entries[index].Text);
        index++;
    }
}

void setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) {
    std::string str = "";
    double xCoordOfFirstValue = entries[index].X;
    do {
        setSentence(str, entries, index);
        value.push_back(str);
    } while(!(entries[index].Y < entries[index - 1].Y) || !(entries[index].X < xCoordOfFirstValue)); 
}

void PDFParser::algorithm(std::stack<std::shared_ptr<ReportComposite>>& nestedComponentStack, 
    std::stack<double>& flags, std::string& line, const std::vector<PdfTextEntry>& entries, int& index) {
        
    double eps = 0.01;
    double xCoordOfFirstWord = 0;
    flags.push(entries[index].X);
    index++;
    setSentence(line, entries, index);
    std::shared_ptr<ReportComposite> rComposite = std::make_shared<ReportComposite>(line);
    if(!nestedComponentStack.empty()) nestedComponentStack.top()->add(rComposite);
    nestedComponentStack.push(rComposite);

    if(entries[index].Text == "") {
        algorithm(nestedComponentStack, flags, line, entries, index);
    } else {
        xCoordOfFirstWord = entries[index].X;
        setSentence(line, entries, index);
        std::string tableName = nestedComponentStack.top()->getName() + " table";

        std::string key;
        std::vector<std::string> value;
        TableDataMap rows;
        
        while (true) {
            key = std::move(line);
            setMapValue(value, entries, index);
            rows.insert({key, value});
            value.clear();

            if(!flags.empty()) {
                if(entries[index].X < flags.top() && entries[index].Text == "") {
                    SettingsDataTable table(tableName, rows);
                    if(!nestedComponentStack.empty()){
                        nestedComponentStack.top()->add(std::make_shared<SettingsDataTable>(table));
                        nestedComponentStack.pop();
                    } 

                    while(flags.top() > entries[index].X && !flags.empty() && !nestedComponentStack.empty()) {
                        flags.pop();
                    }
                    algorithm(nestedComponentStack, flags, line, entries, index);
                    break;
                }

                if(entries[index].X == flags.top() && entries[index].Text == "") {
                    SettingsDataTable table(tableName, rows);
                    if(!nestedComponentStack.empty()){
                        nestedComponentStack.top()->add(std::make_shared<SettingsDataTable>(table));
                        nestedComponentStack.pop();
                    } 
                    algorithm(nestedComponentStack, flags, line, entries, index);
                    break;
                }
                if(entries[index].X > flags.top() && entries[index].Text == "") {
                    algorithm(nestedComponentStack, flags, line, entries, index);
                }
            }
            if(entries[index].X + eps < xCoordOfFirstWord /**/ && entries[index].X < flags.top() /**/
                && entries[index].Y < entries[index - 1].Y && entries[index].Text != "") {
                SettingsDataTable table(tableName, rows);
                if(!nestedComponentStack.empty()){
                    nestedComponentStack.top()->add(std::make_shared<SettingsDataTable>(table));
                    nestedComponentStack.pop();
                } 
                break;
            }
            if(entries[index].X + eps < xCoordOfFirstWord && entries[index].X > flags.top()
                && entries[index].Y < entries[index - 1].Y && entries[index].Text != "") {
                SettingsDataTable table(tableName, rows);
                if(!nestedComponentStack.empty() && !flags.empty()){
                    nestedComponentStack.top()->add(std::make_shared<SettingsDataTable>(table));
                    flags.pop();
                } 
                break;
            }
            xCoordOfFirstWord = entries[index].X;
            setSentence(line, entries, index);
        }
    }
}

void PDFParser::fillReport(const std::vector<PdfTextEntry>& entries) {
    ParsingContext pContext;
    std::string line = entries[0].Text;
    std::string potentialTitle = "";
    for (int i = 1; i < entries.size(); i++) {
        if(entries[i].Y < entries[i - 1].Y) {
            if(entries[i].Text == "") {
                std::stack<std::shared_ptr<ReportComposite>> nestedComponentStack;
                std::stack<double> flags;

                auto root = std::make_shared<ReportComposite>(line);
                nestedComponentStack.push(root); 

                algorithm(nestedComponentStack, flags, line, entries, i);
                while (nestedComponentStack.size() > 1)
                {
                    nestedComponentStack.pop();
                }
                
                aReport_->addTable(*nestedComponentStack.top());
                nestedComponentStack.pop();
                i--;
            } else {
                potentialTitle = line;
                line = entries[i].Text;
            }
        } else {
            if(ParsingStrategy::checkComponentOfSentence(entries[i - 1], entries[i])) {
                line.append(" " + entries[i].Text);
            } else {
                std::stack<ReportComposite> ordinaryComponentStack;
                std::unique_ptr<ParsingOrdinaryTable> ot = std::make_unique<ParsingOrdinaryTable>();
                pContext_.setStrategy(std::move(ot));

                ReportComposite rComposite(potentialTitle);
                ordinaryComponentStack.push(rComposite);

                std::string tableName = "";
                tableName = ordinaryComponentStack.top().getName() + " table";
                TableDataMap c = pContext_.executeParsingStrategy(line, entries, i);
                SettingsDataTable table(tableName, c);
                ordinaryComponentStack.top().add(std::make_shared<SettingsDataTable>(table));
                aReport_->addTable(ordinaryComponentStack.top());
                ordinaryComponentStack.pop();
            }
        }
    }
}
