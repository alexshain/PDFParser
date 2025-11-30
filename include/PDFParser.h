#ifndef PDF_PARSER
#define PDF_PARSER

#include <podofo/podofo.h>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "AnsysReport/AnsysReport.h"

class PDFParser {
private:
    std::unique_ptr<AnsysReport> ansysReport;
};

#endif