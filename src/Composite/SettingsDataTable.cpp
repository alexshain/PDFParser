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

void SettingsDataTable::write(std::string indent) const {
    std::cout << indent << name_ << "\n";
    for (const auto& pair : rows_) {
        std::cout << indent << "Key: " << pair.first << " Values: ";
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

void SettingsDataTable::setParent(std::shared_ptr<Component> parent) {
    parent_ = parent;
}

std::shared_ptr<Component> SettingsDataTable::getParent() const {
    return parent_.lock();
}

std::string SettingsDataTable::getPath() const {
    return parent_.lock()->getPath();
}