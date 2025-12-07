#include "AnsysReport/AnsysReport.h"
#include "Composite/ReportComposite.h"
#include "Composite/SettingsDataTable.h"
#include "PDFParser.h"

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
        

        std::vector<PoDoFo::PdfTextEntry> globalEntries;

        for(int i = 0; i < document.GetPages().GetCount(); i++) {
            std::vector<PoDoFo::PdfTextEntry> entries;
        
            PdfTextExtractParams params;
            params.Flags = PdfTextExtractFlags::TokenizeWords;
            PdfPage& page = document.GetPages().GetPageAt(i);
            page.ExtractTextTo(entries, params);

            int factor = document.GetPages().GetCount() - i;
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

        for (const auto& entry : globalEntries) {
            std::cout << entry.Text << " (x, y) = " << "(" << entry.X << "," << entry.Y << ") " << "Length: " << entry.Length << std::endl;
        }
        
    } catch (PdfError& e) {
        std::cerr << "Error reading PDF: " << e.what() << std::endl;
    }
}

int main() {

    //readFile("Ansys_Fluent_Simulation_Report.pdf");

    /*
    std::string fluentFile1 = "";
    std::string fluentFile2 = "";

    PDFParser parser(fluentFile1);

    std::unique_ptr<AnsysReport> aReport1 = parser.parse();

    parser.reset(fluentFile2);

    std::unique_ptr<AnsysReport> aReport2 = parser.parse();
    */

    std::string fluentFile1 = "Ansys_Fluent_Simulation_Report.pdf";

    PDFParser parser(fluentFile1);

    std::unique_ptr<AnsysReport> aReport1 = parser.parse();
    aReport1->wtireToConsole();

    return 0;
}
