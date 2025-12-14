#ifndef PARSING_NESTED_TABLE
#define PARSING_NESTED_TABLE

#include "ParsingStrategy.h"

class ParsingNestedTable : public ParsingStrategy 
{
public:
    void execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, TableDataMap& dMap) const override;
};

#endif