#include "PDFParser.h"
#include "Composite/ReportComposite.h"
#include "Composite/SettingsDataTable.h"
#include "ParsingStrategy/ParsingContext.h"
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

// не забыть добавить парсинг с нескольких страниц
void PDFParser::fillReport(const std::vector<PdfTextEntry>& entries) {
    ParsingContext pContext;
    std::string line = entries[0].Text;
    std::string potentialTitle;
    double flag = 0;
    for (int i = 1; i < entries.size(); i++) {
        std::cout << line << std::endl;
        if(entries[i].Y < entries[i - 1].Y) {
            if(entries[i].Text == "") {
                flag = entries[i].X;
                std::unique_ptr<ParsingNestedTable> nt = std::make_unique<ParsingNestedTable>();
                pContext.setStrategy(std::move(nt));
                while(true && i < entries.size()) {
                    ReportComposite rComposite(line);
                    componentStack_.push(rComposite);

                    while(entries[i].Text == "") {
                        if(i < entries.size() - 1) { 
                            i++;
                        } else break;
                        flag = entries[i].X;
                        ParsingStrategy::setSentence(line, entries, i);
                        rComposite = ReportComposite(line);
                        componentStack_.push(rComposite);
                    }
                    
                    //отрефакторить
                    std::string tableName = "";
                    if(!componentStack_.empty()) tableName = componentStack_.top().getName() + " table";
                    TableDataMap c = pContext.executeParsingStrategy(line, entries, i);
                    std::shared_ptr<SettingsDataTable> dTable = std::make_shared<SettingsDataTable>(tableName, c);
                    if(!componentStack_.empty()) componentStack_.top().add(rComposite);
                    if(!componentStack_.empty()) componentStack_.pop();
                    
                    //i++;
                    if(entries[i].Text == "" && flag == entries[i].X) {
                        //отрефакторить
                        std::string tableName = "";
                        if(!componentStack_.empty()) tableName = componentStack_.top().getName() + " table";
                        TableDataMap c = pContext.executeParsingStrategy(line, entries, i);
                        dTable = std::make_shared<SettingsDataTable>(tableName, c);
                        if(!componentStack_.empty()) componentStack_.top().add(rComposite);
                        if(!componentStack_.empty()) componentStack_.pop();
                    } else if(entries[i].Text == "" && flag > entries[i].X) {
                        if(!componentStack_.empty()) componentStack_.pop();

                        //отрефакторить
                        while(entries[i].Text == "") {
                            if(i < entries.size() - 1) { 
                                i++;
                            } else break;
                            flag = entries[i].X;
                            ParsingStrategy::setSentence(line, entries, i);
                            rComposite = ReportComposite(line);
                            componentStack_.push(rComposite);
                        }
                        std::string tableName = "";
                        if(!componentStack_.empty()) tableName = componentStack_.top().getName() + " table";
                        TableDataMap c = pContext.executeParsingStrategy(line, entries, i);
                        dTable = std::make_shared<SettingsDataTable>(tableName, c);
                        if(!componentStack_.empty()) componentStack_.top().add(rComposite);
                        if(!componentStack_.empty()) componentStack_.pop();
                    } else if(entries[i].Text != "") {
                        line = entries[i].Text;
                        while(componentStack_.size() != 1) {
                            if(!componentStack_.empty()) componentStack_.pop();
                        }
                        if(!componentStack_.empty()) aReport_->addTable(componentStack_.top());
                        if(!componentStack_.empty()) componentStack_.pop();
                        break;
                    }
                }
            } else {
                potentialTitle = line;
                line = entries[i].Text;
            }
        } else {
            if(ParsingStrategy::checkComponentOfSentence(entries[i - 1], entries[i])) {
                //std::cout << i << std::endl;
                
                line.append(" " + entries[i].Text);
                //std::cout << line << std::endl;
            } else {
                std::unique_ptr<ParsingOrdinaryTable> ot = std::make_unique<ParsingOrdinaryTable>();
                pContext.setStrategy(std::move(ot));

                ReportComposite rComposite(potentialTitle);
                componentStack_.push(rComposite);

                //отрефактоорить
                std::string tableName = "";
                if(!componentStack_.empty()) tableName = componentStack_.top().getName() + " table";

                TableDataMap c = pContext.executeParsingStrategy(line, entries, i);

                SettingsDataTable table(tableName, c);
                if(!componentStack_.empty()) componentStack_.top().add(table);

                if(!componentStack_.empty()) aReport_->addTable(componentStack_.top());

                if(!componentStack_.empty()) componentStack_.pop();
            }
        }
    }
}
