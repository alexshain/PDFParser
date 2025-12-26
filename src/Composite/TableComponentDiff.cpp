#include "Composite/TableComponentDiff.h"

#include <iostream>

bool TableDiff::hasDifferences() const {
    return !onlyInFirst.empty() || 
           !onlyInSecond.empty() || 
           !differentRows.empty();
}

TableComponentDiff::TableComponentDiff(const std::string& path, const std::string& name)
        : ComponentDiffBase(path, name) {}
    
void TableComponentDiff::print(int indent) const {
    std::string indentStr(indent * 2, ' ');
    
    /*if (!path.empty()) {
        //std::cout << indentStr << "Путь: ";
        std::cout << "Путь: ";
        for(int i = 0; i < path.size() - 1; ++i) {
            std::cout << path[i] << " -> ";
        }
    }*/
    //std::cout << componentName << " (Table):\n";
    std::cout << "Путь: ";
    std::cout << path << ":\n";

    if (tableDiff.hasDifferences()) {
        if (!tableDiff.onlyInFirst.empty()) {
            //std::cout << indentStr << "  Строки только в первом:\n";
            std::cout << "  Строки только в первом:\n";
            for (const auto& key : tableDiff.onlyInFirst) {
                //std::cout << indentStr << "    - " << key << "\n";
                std::cout << "    - " << key << "\n";
            }
            std::cout << "\n";
        }
        
        if (!tableDiff.onlyInSecond.empty()) {
            //std::cout << indentStr << "  Строки только во втором:\n";
            std::cout << "  Строки только во втором:\n";
            for (const auto& key : tableDiff.onlyInSecond) {
                //std::cout << indentStr << "    - " << key << "\n";
                std::cout << "    - " << key << "\n";
            }
            std::cout << "\n";
        }
        
        if (!tableDiff.differentRows.empty()) {
            //std::cout << indentStr << "  Строки с разными значениями:\n";
            std::cout << "  Строки с разными значениями:\n";
            for (const auto& [key, values] : tableDiff.differentRows) {
                std::cout << indentStr << "    Ключ: " << key << "\n";
                std::cout << indentStr << "      Первое: ";
                for (const auto& v : values.first) std::cout << v << ", ";
                std::cout << "\n" << indentStr << "      Второе: ";
                for (const auto& v : values.second) std::cout << v << ", ";
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    } else {
        std::cout << indentStr << "  Таблицы идентичны\n";
    }
}

bool TableComponentDiff::hasDifferences() const {
    return tableDiff.hasDifferences();
}