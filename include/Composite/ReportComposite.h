#ifndef REPORT_COMPONENT
#define REPORT_COMPONENT

#include "Component.h"
#include <vector>
#include <memory>

class ReportComposite final : public Component, 
                              public std::enable_shared_from_this<ReportComposite> {
private:
    std::string name_;
    std::vector<std::shared_ptr<Component>> children_;
    std::weak_ptr<Component> parent_;

public:
    ReportComposite(const std::string& name);
    void write(std::string indent) const override;
    void add(std::shared_ptr<Component> component);
    bool isComposite() const override;
    void setParent(std::shared_ptr<Component> parent) override;
    std::shared_ptr<Component> getParent() const override;
    std::string getName() const override;
    std::string getPath() const override;
    std::vector<std::shared_ptr<Component>> getChildren() const override;
};

#endif