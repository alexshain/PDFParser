#include "ParsingStrategy/ParsingOrdinaryTable.h"
#include "Composite/SettingsDataTable.h"
#include "Composite/ReportComposite.h"

void ParsingOrdinaryTable::execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const {
    std::string tableName = "";
    tableName = aReport->getTables().back().getName() + " table"; //ordinaryComponentStack.top().getName() + " table";
    
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

void ParsingOrdinaryTable::setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) const {
    line = entries[index].Text;
    index++;
    while(checkComponentOfSentence(entries[index - 1], entries[index]) && entries[index - 1].Y == entries[index].Y) {
        line.append(" " + entries[index].Text);
        index++;
    }
}

void ParsingOrdinaryTable::setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) const {
    std::string str = "";
    PdfTextEntry firstEntry;
    double y_min = entries[index].Y;

    do {
        firstEntry = entries[index];
        int tempInd = index;
        setSentence(str, entries, index);

        for(int i = tempInd; i < entries.size(); ++i) {
            if(entries[i].Y < y_min && entries[i].X < firstEntry.X) {
                break;
            } else if(entries[i].Y < firstEntry.Y && firstEntry.X == entries[i].X) {
                if(entries[i].Y < y_min)
                    y_min = entries[i].Y;
                firstEntry = entries[i];
                std::string tempLine = "";
                setSentence(tempLine, entries, i);
                str.append(" " + tempLine);
                --i;
            }
        }

        value.push_back(str);
    } while(!(entries[index].Y < entries[index - 1].Y)); 

    while(entries[index].Y >= y_min) {  
        index++;
    }
}