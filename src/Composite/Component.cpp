#include "Composite/Component.h"

void Component::setParent(std::shared_ptr<Component>&& parent) {
    parent_ = parent;
}

std::shared_ptr<Component> Component::getParent() const {
    return parent_.lock();
}