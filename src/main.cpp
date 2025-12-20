#include "AnsysReport/AnsysReport.h"
#include "Composite/ReportComposite.h"
#include "Composite/SettingsDataTable.h"
#include "PDFParser.h"
#include "CompareFunctions.h"

#include <iostream>
#include <podofo/podofo.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace PoDoFo;

void compareAllTables(const std::vector<std::shared_ptr<ReportComposite>>& tables1,
    const std::vector<std::shared_ptr<ReportComposite>>& tables2) {

    // Собираем все имена таблиц
    std::map<std::string, std::pair<std::shared_ptr<ReportComposite>, 
                                    std::shared_ptr<ReportComposite>>> tableMap;

    // Добавляем таблицы из первого файла
    for (const auto& table : tables1) {
        tableMap[table->getName()].first = table;
    }

    // Добавляем таблицы из второго файла
    for (const auto& table : tables2) {
        tableMap[table->getName()].second = table;
    }

    // Сравниваем все таблицы
    for (const auto& [tableName, tables] : tableMap) {
        const auto& [table1, table2] = tables;

        if (table1 && table2) {
            // Таблица есть в обоих файлах - передаем ОРИГИНАЛЫ
            std::cout << "\n=== Сравнение таблицы '" << tableName << "' ===\n";
            if(tableName == "Boundary Conditions") {
                compareAndPrint(table1, table2);  // ИЗМЕНИТЕ ЗДЕСЬ!
                break;
            }
            
        }
        else if (table1) {
            // Таблица есть только в первом файле
            std::cout << "\n=== Таблица '" << tableName << "' есть только в ПЕРВОМ файле ===\n";
        }
        else if (table2) {
            // Таблица есть только во втором файле
            std::cout << "\n=== Таблица '" << tableName << "' есть только во ВТОРОМ файле ===\n";
        }
    }
}

void debugTableComparison(const std::vector<std::shared_ptr<ReportComposite>>& tables1,
                         const std::vector<std::shared_ptr<ReportComposite>>& tables2) {
    
    std::cout << "\n=== ДИАГНОСТИКА ===\n";
    std::cout << "Первый файл: " << tables1.size() << " таблиц\n";
    std::cout << "Второй файл: " << tables2.size() << " таблиц\n\n";
    
    // Выводим все таблицы с их типами
    std::cout << "Таблицы в первом файле:\n";
    for (size_t i = 0; i < tables1.size(); ++i) {
        const auto& table = tables1[i];
        std::cout << "  [" << i << "] " << table->getName();
        
        // Проверяем, что внутри
        auto children = table->getChildren();
        std::cout << " (детей: " << children.size() << "): ";
        
        for (const auto& child : children) {
            if (auto settingsTable = std::dynamic_pointer_cast<SettingsDataTable>(child)) {
                std::cout << "SettingsDataTable[" << settingsTable->getRows().size() << " строк] ";
            } else if (auto reportComp = std::dynamic_pointer_cast<ReportComposite>(child)) {
                std::cout << "ReportComposite[" << reportComp->getName() << "] ";
            }
        }
        std::cout << "\n";
    }
    
    std::cout << "\nТаблицы во втором файле:\n";
    for (size_t i = 0; i < tables2.size(); ++i) {
        const auto& table = tables2[i];
        std::cout << "  [" << i << "] " << table->getName();
        
        auto children = table->getChildren();
        std::cout << " (детей: " << children.size() << "): ";
        
        for (const auto& child : children) {
            if (auto settingsTable = std::dynamic_pointer_cast<SettingsDataTable>(child)) {
                std::cout << "SettingsDataTable[" << settingsTable->getRows().size() << " строк] ";
            } else if (auto reportComp = std::dynamic_pointer_cast<ReportComposite>(child)) {
                std::cout << "ReportComposite[" << reportComp->getName() << "] ";
            }
        }
        std::cout << "\n";
    }
}

int main() {

    /*std::string fluentFile1 = "Ansys_Fluent_Simulation_Report_sort2.pdf";

    std::shared_ptr<AnsysReport> aReport1;

    PDFParser parser(fluentFile1);
    aReport1 = parser.parse();

    aReport1->wtireToConsole();*/

    //std::cout << aReport1->getTables()[2]->getChildren().size() << "\n";

    std::string fluentFile1 = "Ansys_Fluent_Simulation_Report_sort2.pdf";
    std::string fluentFile2 = "Ansys_Fluent_Simulation_Report3.pdf";

    std::shared_ptr<AnsysReport> aReport1;
    std::shared_ptr<AnsysReport> aReport2;

    PDFParser parser(fluentFile1);
    aReport1 = parser.parse();

    PDFParser parser2(fluentFile2);
    aReport2 = parser2.parse();

    std::vector<std::shared_ptr<ReportComposite>> tables1 = aReport1->getTables();
    std::vector<std::shared_ptr<ReportComposite>> tables2 = aReport2->getTables();
    
    //debugTableComparison(tables1, tables2);

    //compareAllTables(tables1, tables2);

    for(int i = 0; i < tables1.size(); ++i) {
        for(int j = 0; j < tables2.size(); ++j) {
            if(tables1[i]->getName() == tables2[j]->getName()) {
                std::cout << "==== " << tables1[i]->getName() << " ======" << "\n";
                compareAndPrint(tables1[i], tables2[j]);
                break;
            }
        }
    }




    return 0;
}
