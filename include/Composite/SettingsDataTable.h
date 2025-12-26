#ifndef SETTINGS_DATA_TABLE
#define SETTINGS_DATA_TABLE

#include "Component.h"

#include <string>
#include <unordered_map>

using TableDataMap = std::unordered_map<std::string, std::vector<std::string>>;

class SettingsDataTable final : public Component, 
                                public std::enable_shared_from_this<SettingsDataTable> {
private:
    std::string name_;
    TableDataMap rows_;
    std::weak_ptr<Component> parent_;

public:
    SettingsDataTable(const std::string& name, const TableDataMap& rows);
    void write(std::string indent) const override;
    const TableDataMap& getRows() const;
    bool isComposite() const override;
    void setParent(std::shared_ptr<Component> parent) override;
    std::shared_ptr<Component> getParent() const override;
    std::string getName() const override;
    std::string getPath() const override;
    std::vector<std::shared_ptr<Component>> getChildren() const override;
};

#endif