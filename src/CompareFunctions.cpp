#include "CompareFunctions.h"
#include "Composite/CompositeComponentDiff.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

TableDiff compareTableDataMaps(
    const TableDataMap& map1,
    const TableDataMap& map2) {
    
    TableDiff diff;
    
    for (const auto& [key, value1] : map1) {
        auto it2 = map2.find(key);
        if (it2 == map2.end()) {
            diff.onlyInFirst.push_back(key);
        } else if (value1 != it2->second) {
            diff.differentRows[key] = {value1, it2->second};
        }
    }
    
    for (const auto& [key, value2] : map2) {
        if (map1.find(key) == map1.end()) {
            diff.onlyInSecond.push_back(key);
        }
    }
    
    return diff;
}

std::unique_ptr<ComponentDiffBase> compareComponents(
    const std::shared_ptr<Component>& comp1,
    const std::shared_ptr<Component>& comp2,
    const std::vector<std::string>& currentPath) {
    
    std::vector<std::string> newPath = currentPath;
    newPath.push_back(comp1->getName());
    
    if (auto table1 = std::dynamic_pointer_cast<SettingsDataTable>(comp1)) {
        auto table2 = std::dynamic_pointer_cast<SettingsDataTable>(comp2);

        auto tableDiff = std::make_unique<TableComponentDiff>(comp1->getPath(), comp1->getName());
        tableDiff->tableDiff = compareTableDataMaps(
            table1->getRows(), 
            table2->getRows()
        );
        
        return tableDiff;
        
    } else if (auto composite1 = std::dynamic_pointer_cast<ReportComposite>(comp1)) {
        auto composite2 = std::dynamic_pointer_cast<ReportComposite>(comp2);
        
        auto compositeDiff = std::make_unique<CompositeComponentDiff>(comp1->getPath(), comp1->getName());
        
        const auto& children1 = composite1->getChildren();
        const auto& children2 = composite2->getChildren();
        
        if (children1.size() != children2.size()) {
            compositeDiff->differentChildCount = true;
            compositeDiff->firstChildCount = children1.size();
            compositeDiff->secondChildCount = children2.size();
        }
        
        size_t minSize = std::min(children1.size(), children2.size());
        for (size_t i = 0; i < minSize; ++i) {
            auto childDiff = compareComponents(children1[i], children2[i], newPath);
            if (childDiff->hasDifferences()) {
                compositeDiff->childrenDiffs.push_back(std::move(childDiff));
            }
        }
        
        return compositeDiff;
    }
    
    return std::make_unique<CompositeComponentDiff>("", comp1->getName());
}

void printComponentDiff(const ComponentDiffBase& diff) {
    diff.print();
    
    if (!diff.hasDifferences()) {
        std::cout << "Компоненты идентичны!\n";
    }
}

bool compareAndPrint(const std::shared_ptr<Component>& comp1,
                     const std::shared_ptr<Component>& comp2) {
    
    auto diff = compareComponents(comp1, comp2);
    std::cout << "\n" << comp1->getName() << ": ";
    
    if (diff->hasDifferences()) {
        std::cout << "\nНайдены различия:\n";
        printComponentDiff(*diff);
        return false;
    } else {
        std::cout << "Компоненты идентичны!\n";
        return true;
    }
}
