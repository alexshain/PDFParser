#ifndef COMPONENT
#define COMPONENT

#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

class Component {
public:
    virtual void setParent(std::shared_ptr<Component> parent) = 0;
    virtual std::shared_ptr<Component> getParent() const = 0;
    virtual std::string getName() const = 0;
    virtual std::vector<std::shared_ptr<Component>> getChildren() const = 0;
    virtual bool isComposite() const = 0;
    virtual void write(std::string indent) const = 0;
    virtual std::string getPath() const = 0;
    virtual ~Component() = default;
};

#endif