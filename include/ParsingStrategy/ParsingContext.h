#ifndef PARSING_CONTEXT
#define PARSING_CONTEXT

#include "ParsingStrategy.h"
#include "Composite/ReportComposite.h"
#include "AnsysReport/AnsysReport.h"

#include <memory>

class ParsingContext 
{
    std::unique_ptr<ParsingStrategy> strategy_;

public:
    void setStrategy(std::unique_ptr<ParsingStrategy>&& strategy);

    void executeParsingStrategy(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const;
};

#endif