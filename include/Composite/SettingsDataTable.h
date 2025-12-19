#ifndef SETTINGS_DATA_TABLE
#define SETTINGS_DATA_TABLE

#include "Component.h"

#include <string>
#include <unordered_map>

using TableDataMap = std::unordered_map<std::string, std::vector<std::string>>;

class SettingsDataTable final : public Component {
private:
    std::string name_;
    TableDataMap rows_;

public:
    SettingsDataTable(const std::string& name, const TableDataMap& rows);
    std::string getName() const override;
    std::vector<std::shared_ptr<Component>> getChildren() const override;
    void write() const override;
    const TableDataMap& getRows() const;
    bool isComposite() const override;
};

#endif