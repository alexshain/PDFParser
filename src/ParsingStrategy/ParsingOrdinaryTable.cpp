#include "ParsingStrategy/ParsingOrdinaryTable.h"
#include "Composite/SettingsDataTable.h"
#include "Composite/ReportComposite.h"

void ParsingOrdinaryTable::execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, TableDataMap& rows) const {
    std::string key;
    std::vector<std::string> value;
    double xCoordOfFirstWord = 0;

    while (true) {
        key = std::move(line);
        ParsingStrategy::setMapValue(value, entries, index);
        rows.insert({key, value});

        value.clear();
        
        double eps = 0.01;
        if(entries[index].X + eps < xCoordOfFirstWord && entries[index].Y < entries[index - 1].Y) { 
            line = entries[index].Text;
            //index--;
            break;
        }
        
        xCoordOfFirstWord = entries[index].X;
        setSentence(line, entries, index);
    }
    
} 