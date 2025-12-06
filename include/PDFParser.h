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
    std::unique_ptr<AnsysReport> ansysReport;

public: 
    explicit PDFParser(const std::string& filename);
    void parse();

private:
    void readFile();
    void fillChapter(const std::vector<PoDoFo::PdfTextEntry>& entries);
    bool isTitle();
};

#endif