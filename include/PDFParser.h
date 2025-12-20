#ifndef PDF_PARSER
#define PDF_PARSER

#include <podofo/podofo.h>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <set>

#include "AnsysReport/AnsysReport.h"
#include "ParsingStrategy/ParsingContext.h"

using namespace PoDoFo;

class PDFParser {
private:
    std::string filename_;
    PdfMemDocument document_;
    const std::set<std::string> ordinaryTableNames = {"Models", "Reference Values", "Named Expressions"};
    const std::set<std::string> nestedTableNames = {"Material Properties"
                                                    , "Cell Zone Conditions"
                                                    , "Boundary Conditions"
                                                    , "Solver Settings"};

public: 
    explicit PDFParser(const std::string& filename);
    std::shared_ptr<AnsysReport> parse();
    void reset(const std::string& filename);

private:
    void setDocument();
    void fillReport(const std::vector<PoDoFo::PdfTextEntry>& entries);
    
private:
    ParsingContext pContext_;
    std::shared_ptr<AnsysReport> aReport_;
};

#endif