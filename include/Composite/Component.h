#ifndef COMPONENT
#define COMPONENT

#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

class Component {
protected:
    std::weak_ptr<Component> parent_;

public:
    void setParent(std::shared_ptr<Component>&& parent);
    std::shared_ptr<Component> getParent() const;
    virtual std::string getName() const = 0;
    virtual std::vector<Component*> getChildren() const = 0;
    virtual bool isComposite() const = 0;
    virtual void write() const = 0;
    virtual ~Component() = default;
};

#endif