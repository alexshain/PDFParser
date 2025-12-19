#include "ParsingStrategy/ParsingOrdinaryTable.h"
#include "Composite/SettingsDataTable.h"
#include "Composite/ReportComposite.h"

void ParsingOrdinaryTable::execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const {
    std::string tableName = "";
    tableName = aReport->getTables().back().getName() + " table";
    
    std::string key;
    std::vector<std::string> value;
    TableDataMap rows;
    double xCoordOfFirstWord = 0;

    while (true) {
        key = std::move(line);
        setMapValue(value, entries, index);
        rows.insert({key, value});

        value.clear();
        
        double eps = 0.01;
        if(entries[index].X + eps < xCoordOfFirstWord && entries[index].Y < entries[index - 1].Y) { 
            line = entries[index].Text;
            break;
        }
        
        xCoordOfFirstWord = entries[index].X;
        setSentence(line, entries, index);
    }

    SettingsDataTable table(tableName, rows);
    aReport->getTables().back().add(std::make_shared<SettingsDataTable>(table));
} 

bool ParsingOrdinaryTable::checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) const {
    double maxSpaceLength = (prevEntry.Length / prevEntry.Text.size()) * 13;
    double spaceLength = currEntry.X - prevEntry.X - prevEntry.Length;
    return spaceLength < maxSpaceLength;
}

void ParsingOrdinaryTable::setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) const {
    str_ = "";
    y_min_ = entries[index].Y;

    do {
        firstEntry_ = entries[index];
        int tempInd = index;
        setSentence(str_, entries, index);

        setElementOfMapValue(tempInd, entries);

        value.push_back(str_);
    } while(!(entries[index].Y < entries[index - 1].Y)); 

    while(entries[index].Y >= y_min_) {  
        index++;
    }
}

void ParsingOrdinaryTable::setElementOfMapValue(int tempInd, const std::vector<PdfTextEntry>& entries) const {
    for(int i = tempInd; i < entries.size(); ++i) {
        if(entries[i].Y < y_min_ && entries[i].X < firstEntry_.X) {
            break;
        } else if(entries[i].Y < firstEntry_.Y && firstEntry_.X == entries[i].X) {
            if(entries[i].Y < y_min_)
                y_min_ = entries[i].Y;
            firstEntry_ = entries[i];
            std::string tempLine = "";
            setSentence(tempLine, entries, i);
            str_.append(" " + tempLine);
            --i;
        }
    }
}