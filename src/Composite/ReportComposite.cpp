#include "Composite/ReportComposite.h"

ReportComposite::ReportComposite(const std::string& name) : name_(name) {}

std::string ReportComposite::getName() const {
    return name_;
}

const std::vector<std::shared_ptr<Component>>& ReportComposite::getChildren() const {
    return children_;
}

void ReportComposite::add(std::shared_ptr<Component> component) {
    children_.push_back(component);
}

bool ReportComposite::isComposite() const {
    return true;
}