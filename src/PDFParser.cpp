#include "PDFParser.h"

#include <iostream>
#include <algorithm>

explicit PDFParser::PDFParser(const std::string& filename) : filename_(filename) {}

void PDFParser::parse() {
    // Итерируемся по страницам
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

void PDFParser::readFile() {
    try {
        document_.Load(filename_);
    } catch (PdfError& e) {
        std::cerr << "Error reading PDF: " << e.what() << std::endl;
    }
}

void PDFParser::fillChapter(const std::vector<PdfTextEntry>& entries) {
    std::string line = entries[0].Text;
    double currentY = entries[0].Y;
    for (int i = 1; i < entries.size(); i++) {
        double maxSpaceLength = (entries[i].Length / entries[i].Text.size()) * 7; //эмпирический подбор
        double spaceLength = entries[i].X - entries[i - 1].X - entries[i - 1].Length;
        if(spaceLength < maxSpaceLength) {
            line += entries[i].Text;
        }
    }
}