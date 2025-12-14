#ifndef PDF_PARSER
#define PDF_PARSER

#include <podofo/podofo.h>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "AnsysReport/AnsysReport.h"
#include "ParsingStrategy/ParsingContext.h"

using namespace PoDoFo;

class PDFParser {
private:
    std::string filename_;
    PdfMemDocument document_;

public: 
    explicit PDFParser(const std::string& filename);
    std::unique_ptr<AnsysReport> parse();
    void reset(const std::string& filename);

private:
    void setDocument();
    void fillReport(const std::vector<PoDoFo::PdfTextEntry>& entries);
    void algorithm(std::stack<std::shared_ptr<ReportComposite>>& nestedComponentStack, 
        std::stack<double>& flags, std::string& line, const std::vector<PdfTextEntry>& entries, int& index);
    
private:
    ParsingContext pContext_;
    std::unique_ptr<AnsysReport> aReport_;
};

#endif