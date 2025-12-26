#ifndef COMPONENT_DIFF_BASE
#define COMPONENT_DIFF_BASE

#include <vector>
#include <string>

struct ComponentDiffBase {
    std::string path; // Путь к компоненту (имена родителей)
    std::string componentName;
    
    ComponentDiffBase(const std::string& path, const std::string& name);
    
    virtual ~ComponentDiffBase() = default;
    virtual void print(int indent = 0) const = 0;
    virtual bool hasDifferences() const = 0;
};

#endif