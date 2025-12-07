#include "PDFParser.h"
#include "ReportComposite.h"
#include "SettingsDataTable.h"
#include "ParsingStrategy/ParsingContext.h"
#include "ParsingStrategy/ParsingOrdinaryTable.h"
#include "ParsingStrategy/ParsingNestedTable.h"

#include <iostream>
#include <algorithm>

PDFParser::PDFParser(const std::string& filename) : filename_(filename) {
    setDocument();
}

std::unique_ptr<AnsysReport> PDFParser::parse() {
    for(int i = 0; i < document_.GetPages().GetCount(); i++) {
        std::vector<PoDoFo::PdfTextEntry> entries;
    
        PdfTextExtractParams params;
        params.Flags = PdfTextExtractFlags::TokenizeWords;
        PdfPage& page = document_.GetPages().GetPageAt(i);
        page.ExtractTextTo(entries, params);

        std::sort(entries.begin(), entries.end(), 
                [](PdfTextEntry& a, PdfTextEntry& b) {
                    if(a.Y != b.Y)
                        return a.Y > b.Y;
                    return a.X < b.X;
                });

        if(entries.size() != 0) {
            fillChapter(entries);
        }
    }
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
void PDFParser::fillChapter(const std::vector<PdfTextEntry>& entries) {
    ParsingContext pContext;
    std::string line = entries[0].Text;
    double currentY = entries[0].Y;
    for (int i = 1; i < entries.size(); i++) {
        if(entries[i].Y < currentY) {
            if(entries[i].Text == "") {
                std::unique_ptr<ParsingNestedTable> nt = std::make_unique<ParsingNestedTable>();
                pContext.setStrategy(std::move(nt));
                pContext.executeParsingStrategy(line, entries, i);
            } 

            ReportComposite rComposite(line);
            componentStack_.push(rComposite);
            line = entries[i].Text;
        } else {
            if(ParsingStrategy::checkComponentOfSentence(entries[i - 1], entries[i])) {
                line.append(" " + entries[i].Text);
            } else {
                std::unique_ptr<ParsingOrdinaryTable> ot = std::make_unique<ParsingOrdinaryTable>();
                pContext.setStrategy(std::move(ot));
                std::string tableName = componentStack_.top().getName() + " table";
                std::shared_ptr<TableDataMap> c = pContext.executeParsingStrategy(line, entries, i);
                std::shared_ptr<SettingsDataTable> rComposite = std::make_shared<SettingsDataTable>(tableName, c);
                componentStack_.top().add(rComposite);



                /*std::string name = std::move(line);
                ParsingStrategy::setSentence(line, entries, i);
                std::string key = std::move(line);
                std::vector<std::string> value;
                ParsingStrategy::setMapValue(value, entries, i, currentY);

                TableDataMap rows{{key, value}};
                std::unique_ptr<SettingsDataTable> dTable = std::make_unique<SettingsDataTable>(name, rows);
                std::unique_ptr<ReportComposite> rComposite = std::make_unique<ReportComposite>(componentStack_.top());
                rComposite->add(std::move(dTable));
                componentStack_.pop();
                componentStack_.top().add(std::move(rComposite));*/
            }
        }
        currentY = entries[i].Y;
    }
}
