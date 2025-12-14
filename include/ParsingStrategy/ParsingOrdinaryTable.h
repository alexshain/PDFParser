#ifndef PARSING_ORDINARY_TABLE
#define PARSING_ORDINARY_TABLE

#include "ParsingStrategy.h"

class ParsingOrdinaryTable : public ParsingStrategy 
{
public:
    void execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const override;

public:
    friend class PDFParser;

private:
    bool checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) const override;
    void setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) const override;
    void setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) const override;
};

#endif