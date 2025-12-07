#include "AnsysReport/AnsysReport.h"

void AnsysReport::addTable(std::unique_ptr<Component>&& chapter) {
    tables.push_back(std::move(chapter));
}

const std::vector<std::unique_ptr<Component>>& AnsysReport::getChapters() const {
    return tables;
}

void AnsysReport::wtireToConsole() const {}