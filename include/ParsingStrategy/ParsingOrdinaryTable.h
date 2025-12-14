#ifndef PARSING_ORDINARY_TABLE
#define PARSING_ORDINARY_TABLE

#include "ParsingStrategy.h"

class ParsingOrdinaryTable : public ParsingStrategy 
{
public:
    void execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, TableDataMap& dMap) const override;
};

#endif