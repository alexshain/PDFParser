#include "AnsysReport/AnsysReport.h"

void AnsysReport::addTable(std::unique_ptr<ReportComposite>&& chapter) {
    tables.push_back(std::move(chapter));
}


const std::vector<std::unique_ptr<ReportComposite>>& AnsysReport::getChapters() const {
    return tables;
}