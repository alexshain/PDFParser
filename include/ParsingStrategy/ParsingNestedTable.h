#ifndef PARSING_NESTED_TABLE
#define PARSING_NESTED_TABLE

#include "ParsingStrategy.h"
#include "Composite/ReportComposite.h"

class ParsingNestedTable : public ParsingStrategy 
{
public:
    void execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const override;

private:
    bool checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) const override;
    void setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) const override;

    void algorithm(std::stack<std::shared_ptr<ReportComposite>>& nestedComponentStack
        , std::stack<double>& flags, std::string& line, const std::vector<PdfTextEntry>& entries, int& index) const;

    void addComponentChild(const std::string tableName, const TableDataMap& rows
        , std::stack<std::shared_ptr<ReportComposite>>& nestedComponentStack, std::stack<double>& flags) const;
};

#endif