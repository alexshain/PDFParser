#ifndef ANSYS_REPORT
#define ANSYS_REPORT

#include "ReportComposite.h"

#include <memory>
#include <vector>

class AnsysReport {
private:
    std::vector<std::unique_ptr<Component>> tables;

public:
    void addTable(std::unique_ptr<Component>&& table);
    const std::vector<std::unique_ptr<Component>>& getChapters() const;
    void wtireToConsole() const;
};

#endif