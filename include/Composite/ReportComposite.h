#ifndef REPORT_COMPONENT
#define REPORT_COMPONENT

#include "Component.h"
#include <vector>
#include <memory>

class ReportComposite final : public Component {
private:
    std::vector<std::unique_ptr<Component>> children;

public:
    void add(std::unique_ptr<Component>&& component);
};

#endif