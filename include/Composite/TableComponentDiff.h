#ifndef TABLE_COMPONENT_DIFF
#define TABLE_COMPONENT_DIFF

#include "Composite/ComponentDiffBase.h"

#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::vector;

struct TableDiff {
    std::vector<std::string> onlyInFirst;
    std::vector<std::string> onlyInSecond;
    std::unordered_map<string, std::pair<vector<string>, vector<string>>> differentRows;
    
    bool hasDifferences() const;
};

// Различия для SettingsDataTable
struct TableComponentDiff : public ComponentDiffBase {
    TableDiff tableDiff;
    
    TableComponentDiff(const std::string& path, const std::string& name);
    void print(int indent = 0) const override;
    bool hasDifferences() const override;
};

#endif