#include "Composite/ReportComposite.h"

ReportComposite::ReportComposite(const std::string& name) : name_(name) {}

std::string ReportComposite::getName() const {
    return name_;
}

std::vector<std::shared_ptr<Component>> ReportComposite::getChildren() const {
    return children_;
}

void ReportComposite::write(std::string indent) const {
    std::cout << indent << name_ << "\n";
    indent += "\t";
    for (const auto& component : children_)  {
        if(component == nullptr) {
            continue;
        }
        component->write(indent);
    }
}

void ReportComposite::add(std::shared_ptr<Component> component) {
    children_.push_back(component);
    component->setParent(shared_from_this());
}

bool ReportComposite::isComposite() const {
    return true;
}

void ReportComposite::setParent(std::shared_ptr<Component> parent) {
    parent_ = parent;
}

std::shared_ptr<Component> ReportComposite::getParent() const {
    return parent_.lock();
}

std::string ReportComposite::getPath() const {
    auto parent = parent_.lock();
    if (parent) {
        return parent->getPath() + " -> " + name_;
    }
    return name_;
}
