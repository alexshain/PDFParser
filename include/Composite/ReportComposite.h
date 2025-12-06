#ifndef REPORT_COMPONENT
#define REPORT_COMPONENT

#include "Component.h"
#include <vector>
#include <memory>

class ReportComposite final : public Component {
private:
    std::string name;
    std::vector<std::unique_ptr<Component>> children;

public:
    void add(std::unique_ptr<Component>&& component);
    std::string getName() const;
    const std::vector<std::unique_ptr<Component>>& getChildren() const;
    bool isComposite() const override;
};

#endif