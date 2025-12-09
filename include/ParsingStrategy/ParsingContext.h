#ifndef PARSING_CONTEXT
#define PARSING_CONTEXT

#include "ParsingStrategy.h"
#include "Composite/ReportComposite.h"

#include <memory>

class ParsingContext 
{
    std::unique_ptr<ParsingStrategy> strategy_;

public:
    void setStrategy(std::unique_ptr<ParsingStrategy>&& strategy);

    TableDataMap executeParsingStrategy(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, double xCoordOfFirstWord) const;
};

#endif