#include "Composite/CompositeComponentDiff.h"

#include <iostream>

CompositeComponentDiff::CompositeComponentDiff(const std::string& path, const std::string& name)
        : ComponentDiffBase(path, name) {}
    
void CompositeComponentDiff::print(int indent) const {
    std::string indentStr(indent * 2, ' ');
    
    if (!path.empty()) {
        //std::cout << indentStr << "Путь: ";
        //for (const auto& p : path) {
        //    std::cout << p << " -> ";
        //}
    }
    //std::cout << componentName << " (Composite):\n";
    
    if (differentChildCount) {
        std::cout << indentStr << "  Разное количество детей:\n";
        std::cout << indentStr << "    Первый: " << firstChildCount << " детей\n";
        std::cout << indentStr << "    Второй: " << secondChildCount << " детей\n";
    }
    
    for (const auto& childDiff : childrenDiffs) {
        childDiff->print(indent + 1);
    }
    
    if (!differentChildCount && childrenDiffs.empty()) {
        std::cout << indentStr << "  Композиты идентичны\n";
    }
}

bool CompositeComponentDiff::hasDifferences() const {
    if (differentChildCount) return true;
    
    for (const auto& childDiff : childrenDiffs) {
        if (childDiff->hasDifferences()) {
            return true;
        }
    }
    
    return false;
}