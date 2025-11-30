#ifndef CHAPTER
#define CHAPTER

#include "Composite/SettingsDataMap.h"
#include "Composite/SettingsDataTable.h"
#include "Composite/ReportComposite.h"

#include <memory>

class Chapter {
private:
    std::unique_ptr<ReportComposite> r_composite;
};

#endif