#include "ParsingStrategy/ParsingStrategy.h"


bool ParsingStrategy::checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) {
    double maxSpaceLength = (prevEntry.Length / prevEntry.Text.size()) * 7; //эмпирический подбор
    double spaceLength = currEntry.X - prevEntry.X - prevEntry.Length;
    return spaceLength < maxSpaceLength;
}

void ParsingStrategy::setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) {
    line = "";
    while(checkComponentOfSentence(entries[index - 1], entries[index]) && entries[index - 1].Y == entries[index].Y) {
        line.append(entries[index].Text + " ");
        index++;
    }
}

void ParsingStrategy::setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) {
    std::string str;
    double currentY = entries[index].Y;
    do {
        setSentence(str, entries, index);
        value.push_back(str);
    } while(!(entries[index + 1].Y < currentY));
}