#include "AnsysReport/AnsysReport.h"

void AnsysReport::addTable(ReportComposite chapter) {
    tables.push_back(chapter);
}

const std::vector<ReportComposite>& AnsysReport::getChapters() const {
    return tables;
}

void AnsysReport::wtireToConsole() const {
    for(const auto& table: tables) {
        std::cout << "before table.write();" << std::endl;
        table.write();
    }
}