#include "ParsingStrategy/ParsingStrategy.h"

void ParsingStrategy::setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) const {
    line = entries[index].Text;
    index++;
    while(checkComponentOfSentence(entries[index - 1], entries[index]) && entries[index - 1].Y == entries[index].Y) {
        line.append(" " + entries[index].Text);
        index++;
    }
}