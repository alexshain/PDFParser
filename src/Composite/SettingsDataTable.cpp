#include "Composite/SettingsDataTable.h"

std::string SettingsDataTable::getName() const {
    return name;
}

const TableDataMap& SettingsDataTable::getRows() const {
    return rows;
}

bool SettingsDataTable::isComposite() const {
    return false;
}