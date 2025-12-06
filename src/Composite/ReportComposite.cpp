#include "Composite/ReportComposite.h"

std::string ReportComposite::getName() const {
    return name;
}

const std::vector<std::unique_ptr<Component>>& ReportComposite::getChildren() const {
    return children;
}

void ReportComposite::add(std::unique_ptr<Component>&& component) {
    children.push_back(std::move(component));
}

bool ReportComposite::isComposite() const {
    return true;
}