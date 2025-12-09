#include "ParsingStrategy/ParsingContext.h"
#include "Composite/SettingsDataTable.h"

void ParsingContext::setStrategy(std::unique_ptr<ParsingStrategy>&& strategy) {
    if(strategy) {
        strategy_ = std::move(strategy);
    }
    
}

TableDataMap ParsingContext::executeParsingStrategy(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, double xCoordOfFirstWord) const {
    TableDataMap dMap;
    strategy_->execute(line, entries, index, dMap, xCoordOfFirstWord);
    return dMap;
}