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
    void setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) const override;

private:
    void setElementOfMapValue(int tempInd, const std::vector<PdfTextEntry>& entries) const;

private:
    mutable std::string str_;
    mutable PdfTextEntry firstEntry_;
    mutable double y_min_;
};

#endif