#ifndef ANSYS_REPORT
#define ANSYS_REPORT

#include "Composite/ReportComposite.h"

#include <memory>
#include <vector>

class AnsysReport {
private:
    std::vector<ReportComposite> tables;

public:
    void addTable(ReportComposite table);
    std::vector<ReportComposite>& getTables();
    void wtireToConsole() const;
};

#endif