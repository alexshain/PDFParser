#include "Composite/SettingsDataTable.h"

SettingsDataTable::SettingsDataTable(const std::string& name, const TableDataMap& rows) 
    : name_(name)
    , rows_(rows) {}

std::string SettingsDataTable::getName() const {
    return name_;
}

const TableDataMap& SettingsDataTable::getRows() const {
    return rows_;
}

bool SettingsDataTable::isComposite() const {
    return false;
}