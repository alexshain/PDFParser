#ifndef PDF_PARSER
#define PDF_PARSER

#include <podofo/podofo.h>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "AnsysReport/AnsysReport.h"

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
    
private:
    std::stack<ReportComposite> componentStack_;
    std::unique_ptr<AnsysReport> aReport_;
};

#endif