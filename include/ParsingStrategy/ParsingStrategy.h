#ifndef PARSING_STRATEGY
#define PARSING_STRATEGY

#include "Composite/SettingsDataTable.h"

#include <podofo/podofo.h>

using PoDoFo::PdfTextEntry;

class ParsingStrategy {
public:
    virtual ~ParsingStrategy() = default;
    virtual void execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, TableDataMap& dMap) const = 0;

public:
    friend class PDFParser;

protected:
    static bool checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry);
    static void setSentence(std::string& line, const std::vector<PdfTextEntry>& entries, int& index);
    static void setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index);
};

#endif