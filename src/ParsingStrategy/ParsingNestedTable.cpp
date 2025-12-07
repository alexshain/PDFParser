#include "ParsingStrategy/ParsingNestedTable.h"
#include "Composite/SettingsDataTable.h"

void ParsingNestedTable::execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, TableDataMap& rows) const {
    std::string key;
    std::vector<std::string> value;
    double currentY = entries[index].Y;

    while (true) {
        key = std::move(line);
        ParsingStrategy::setMapValue(value, entries, index);
        rows.insert({key, value});

        index++;
        value.clear();
        setSentence(line, entries, index);

        if(entries[index].Y < entries[index - 1].Y) { 
            break;
        }
    }
}