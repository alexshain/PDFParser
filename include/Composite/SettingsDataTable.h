#ifndef SETTINGS_DATA_TABLE
#define SETTINGS_DATA_TABLE

#include "Component.h"
#include <vector>
#include <string>

class SettingsDataTable final : public Component {
private:
    std::vector<std::string> columns_names;
    std::vector<std::vector<std::string>> rows;
};

#endif