#include "AnsysReport/AnsysReport.h"

void AnsysReport::addTable(ReportComposite chapter) {
    tables.push_back(chapter);
}

std::vector<ReportComposite>& AnsysReport::getTables() {
    return tables;
}

void AnsysReport::wtireToConsole() const {
    for(const auto& table: tables) {
        table.write();
    }
}