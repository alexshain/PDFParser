#include "AnsysReport/AnsysReport.h"

void AnsysReport::addTable(std::shared_ptr<ReportComposite> chapter) {
    tables.push_back(chapter);
}

std::vector<std::shared_ptr<ReportComposite>> AnsysReport::getTables() const {
    return tables;
}

void AnsysReport::wtireToConsole() const {
    for(const auto& table: tables) {
        std::string str = "";
        table->write(str);
    }
}