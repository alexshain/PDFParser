#include "ParsingStrategy/ParsingStrategy.h"

bool ParsingStrategy::checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) {
    double maxSpaceLength = (prevEntry.Length / prevEntry.Text.size()) * 13;
    double spaceLength = currEntry.X - prevEntry.X - prevEntry.Length;
    return spaceLength < maxSpaceLength;
}

void ParsingStrategy::setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) {
    line = entries[index].Text;
    index++;
    while(checkComponentOfSentence(entries[index - 1], entries[index]) && entries[index - 1].Y == entries[index].Y) {
        line.append(" " + entries[index].Text);
        index++;
    }
}

void ParsingStrategy::setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) {
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