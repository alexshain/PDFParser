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

void SettingsDataTable::write() const {
    std::cout << name_ << "\n\t";
    for (const auto& pair : rows_) {
        std::cout << "Key: " << pair.first << " Values: ";
        for (const auto& value : pair.second) {
            std::cout << value << ", ";
        }
        std::cout << "\n";
    }
}

std::vector<std::shared_ptr<Component>> SettingsDataTable::getChildren() const {
    return {};
}

bool SettingsDataTable::isComposite() const {
    return false;
}