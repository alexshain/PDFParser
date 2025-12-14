#ifndef PARSING_STRATEGY
#define PARSING_STRATEGY

#include "Composite/SettingsDataTable.h"
#include "AnsysReport/AnsysReport.h"

#include <podofo/podofo.h>

using PoDoFo::PdfTextEntry;

class ParsingStrategy {
public:
    virtual ~ParsingStrategy() = default;
    virtual void execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const = 0;

public:
    friend class PDFParser;

protected:
    virtual bool checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) const = 0;
    virtual void setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index) const = 0;
    virtual void setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) const = 0;
};

#endif