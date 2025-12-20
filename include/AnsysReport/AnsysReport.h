#ifndef ANSYS_REPORT
#define ANSYS_REPORT

#include "Composite/ReportComposite.h"

#include <memory>
#include <vector>

class AnsysReport {
private:
    std::vector<std::shared_ptr<ReportComposite>> tables;

public:
    void addTable(std::shared_ptr<ReportComposite> chapter);
    std::vector<std::shared_ptr<ReportComposite>> getTables() const;
    void wtireToConsole() const;
};

#endif