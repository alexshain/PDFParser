#ifndef ANSYS_REPORT
#define ANSYS_REPORT

#include "Chapter.h"

#include <memory>
#include <vector>

class AnsysReport {
private:
    std::vector<std::unique_ptr<Chapter>> chapters;

public:
};

#endif