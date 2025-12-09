#include "ParsingStrategy/ParsingNestedTable.h"
#include "Composite/SettingsDataTable.h"

void ParsingNestedTable::execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, TableDataMap& rows, double xCoordOfFirstWord) const {
    std::string key;
    std::vector<std::string> value;
    
    while (true) {
        key = std::move(line);
        ParsingStrategy::setMapValue(value, entries, index);
        rows.insert({key, value});

        value.clear();
        
        if(entries[index].Y < entries[index - 1].Y && entries[index].Text == "") {
            break;
        }

        double eps = 0.01;
        if(entries[index].X + eps < xCoordOfFirstWord && entries[index].Y < entries[index - 1].Y) { 
            //тут скорее должна происходит раскрутка стэка
            line = entries[index].Text;
            break;
        }
        
        xCoordOfFirstWord = entries[index].X;
        setSentence(line, entries, index);
    }
}