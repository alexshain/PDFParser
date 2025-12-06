#ifndef SETTINGS_DATA_TABLE
#define SETTINGS_DATA_TABLE

#include "Component.h"
#include <string>

class SettingsDataTable final : public Component {
private:
    std::string name;
    TableDataMap rows;

public:
    std::string getName() const;
    const TableDataMap& getRows() const;
    bool isComposite() const override;
};

#endif