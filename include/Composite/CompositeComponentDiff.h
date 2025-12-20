#ifndef COMPOSITE_COMPONENT_DIFF
#define COMPOSITE_COMPONENT_DIFF

#include "Composite/ComponentDiffBase.h"

#include <vector>
#include <string>
#include <unordered_map>

// Различия для ReportComposite
struct CompositeComponentDiff : public ComponentDiffBase {
    std::vector<std::unique_ptr<ComponentDiffBase>> childrenDiffs;
    bool differentChildCount = false;
    size_t firstChildCount = 0;
    size_t secondChildCount = 0;
    
    CompositeComponentDiff(const std::string& path, const std::string& name);
    void print(int indent = 0) const override;
    bool hasDifferences() const override;
};

#endif