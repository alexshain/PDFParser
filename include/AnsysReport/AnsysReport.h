#ifndef ANSYS_REPORT
#define ANSYS_REPORT

#include "ReportComposite.h"

#include <memory>
#include <vector>

class AnsysReport {
private:
    std::vector<std::unique_ptr<ReportComposite>> tables;

public:
    void addTable(std::unique_ptr<ReportComposite>&& table);
    const std::vector<std::unique_ptr<ReportComposite>>& getChapters() const;
};

#endif