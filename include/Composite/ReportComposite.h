#ifndef REPORT_COMPONENT
#define REPORT_COMPONENT

#include "Component.h"
#include <vector>
#include <memory>

class ReportComposite final : public Component {
private:
    std::string name_;
    std::vector<std::shared_ptr<Component>> children_;

public:
    ReportComposite(const std::string& name);
    void add(std::shared_ptr<Component> component);
    std::string getName() const;
    const std::vector<std::shared_ptr<Component>>& getChildren() const;
    bool isComposite() const override;
};

#endif