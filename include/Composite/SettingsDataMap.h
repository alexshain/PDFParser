#ifndef SETTINGS_DATA_MAP
#define SETTINGS_DATA_MAP

#include "Component.h"

#include <string>
#include <unordered_map>

class SettingsDataMap final : public Component {
private:
    std::unordered_map<std::string, std::string> data;
};

#endif