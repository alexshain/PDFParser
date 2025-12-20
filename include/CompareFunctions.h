#ifndef COMPARE_FUNCTIONS
#define COMPARE_FUNCTIONS

#include "Composite/TableComponentDiff.h"
#include "Composite/SettingsDataTable.h"
#include "Composite/ReportComposite.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// Функция сравнения TableDataMap
TableDiff compareTableDataMaps(const TableDataMap& map1, const TableDataMap& map2);

// Функция сравнения компонентов
std::unique_ptr<ComponentDiffBase> compareComponents(
    const std::shared_ptr<Component>& comp1,
    const std::shared_ptr<Component>& comp2,
    const std::vector<std::string>& currentPath = {});

// Функция для красивого вывода различий
void printComponentDiff(const ComponentDiffBase& diff);

// Простая функция сравнения с выводом результата
bool compareAndPrint(const std::shared_ptr<Component>& comp1,
                     const std::shared_ptr<Component>& comp2);

#endif