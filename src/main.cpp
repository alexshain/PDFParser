#include <iostream>
#include <podofo/podofo.h>
#include <vector>
#include <string>
#include <sstream>

using namespace PoDoFo;

void readFile(const std::string& filename) {
    try {
        PdfMemDocument document;
        document.Load(filename);
        
        std::cout << "=== PDF Information ===" << std::endl;
        std::cout << "Pages: " << document.GetPages().GetCount() << std::endl;
        
        PdfPage& page = document.GetPages().GetPageAt(1);

        std::vector<PoDoFo::PdfTextEntry> entries;
        
        PdfTextExtractParams params;
        params.Flags = PdfTextExtractFlags::TokenizeWords;
        page.ExtractTextTo(entries, params);
        
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