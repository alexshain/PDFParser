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

std::shared_ptr<AnsysReport> PDFParser::parse() {
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
    return aReport_;
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

void PDFParser::fillReport(const std::vector<PdfTextEntry>& entries) {
    std::string line = entries[0].Text;
    ParsingOrdinaryTable ot;
    ParsingNestedTable nt;
    std::string potentialTitle = "";
    for (int i = 1; i < entries.size(); i++) {
        if(entries[i].Y < entries[i - 1].Y) {
            if(entries[i].Text == "") {
                pContext_.setStrategy(std::make_unique<ParsingNestedTable>(nt));
                pContext_.executeParsingStrategy(line, entries, i, aReport_);
            } else {
                potentialTitle = line;
                line = entries[i].Text;
            }
        } else {
            if(ot.checkComponentOfSentence(entries[i - 1], entries[i])) {
                line.append(" " + entries[i].Text);
            } else {
                pContext_.setStrategy(std::make_unique<ParsingOrdinaryTable>(ot));
                ReportComposite rComposite(potentialTitle);
                aReport_->addTable(rComposite);
                pContext_.executeParsingStrategy(line, entries, i, aReport_);
            }
        }
    }
}
