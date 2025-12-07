#include "ParsingStrategy/ParsingOrdinaryTable.h"
#include "Composite/SettingsDataTable.h"
#include "Composite/ReportComposite.h"

void ParsingOrdinaryTable::execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, TableDataMap& rows) const {
    std::string key;
    std::vector<std::string> value;

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