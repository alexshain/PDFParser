#ifndef PARSING_CONTEXT
#define PARSING_CONTEXT

#include "ParsingStrategy.h"
#include "ReportComposite.h"

#include <memory>

class ParsingContext 
{
    std::unique_ptr<ParsingStrategy> strategy_;

public:
    void setStrategy(std::unique_ptr<ParsingStrategy>&& strategy);

    std::shared_ptr<TableDataMap> executeParsingStrategy(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) const;
};

#endif