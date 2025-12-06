#include <iostream>
#include <podofo/podofo.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace PoDoFo;

void readFile(const std::string& filename) {
    try {
        PdfMemDocument document;
        document.Load(filename);
        
        std::cout << "=== PDF Information ===" << std::endl;
        std::cout << "Pages: " << document.GetPages().GetCount() << std::endl;
        
        PdfPage& page = document.GetPages().GetPageAt(0);

        std::vector<PoDoFo::PdfTextEntry> entries;
        
        PdfTextExtractParams params;
        params.Flags = PdfTextExtractFlags::TokenizeWords;
        page.ExtractTextTo(entries, params);

        std::sort(entries.begin(), entries.end(), 
                [](PdfTextEntry& a, PdfTextEntry& b) {
                    if(a.Y != b.Y)
                        return a.Y > b.Y;
                    return a.X < b.X;
                });

        for (const auto& entry : entries) {
            std::cout << entry.Text << " (x, y) = " << "(" << entry.X << "," << entry.Y << ") " << "Length: " << entry.Length << std::endl;
        }
        
    } catch (PdfError& e) {
        std::cerr << "Error reading PDF: " << e.what() << std::endl;
    }
}

int main() {

    readFile("Ansys_Fluent_Simulation_Report.pdf");

    return 0;
}

//  Закончил реализацию древовидной логики, 
//  Добвил флаг для выбора правильной логики в зависимости от того лист это или нет
//  
//  далее надо реализовать правильный парсинг и построения дерева компонентов
//
//
//
//
//