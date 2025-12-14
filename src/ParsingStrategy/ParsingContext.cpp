#include "ParsingStrategy/ParsingContext.h"
#include "Composite/SettingsDataTable.h"

void ParsingContext::setStrategy(std::unique_ptr<ParsingStrategy>&& strategy) {
    if(strategy) {
        strategy_ = std::move(strategy);
    }
    
}

void ParsingContext::executeParsingStrategy(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const {
    strategy_->execute(line, entries, index, aReport);
}