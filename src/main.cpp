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
namespace fs = std::filesystem;

int main() {

    /*std::string fluentFile1 = "Ansys_Fluent_Simulation_Report_sort2.pdf";

    std::shared_ptr<AnsysReport> aReport1;

    PDFParser parser(fluentFile1);
    aReport1 = parser.parse();

    aReport1->wtireToConsole();*/

    //std::cout << aReport1->getTables()[2]->getChildren().size() << "\n";

    std::cout << "=== Выбор двух PDF файлов ===\n" << std::endl;
    
    // Получаем список всех файлов в директории
    std::vector<std::string> files;
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            // Проверяем расширение (без учета регистра)
            if (ext.size() >= 4 && 
                std::tolower(ext[ext.size()-4]) == '.' &&
                std::tolower(ext[ext.size()-3]) == 'p' &&
                std::tolower(ext[ext.size()-2]) == 'd' &&
                std::tolower(ext[ext.size()-1]) == 'f') {
                files.push_back(entry.path().filename().string());
            }
        }
    }
    
    if (files.empty()) {
        std::cout << "PDF файлы не найдены в текущей директории!" << std::endl;
        return 1;
    }
    
    // Выводим список файлов
    std::cout << "Найдены следующие PDF файлы:\n";
    for (size_t i = 0; i < files.size(); ++i) {
        std::cout << "  " << i + 1 << ". " << files[i] << std::endl;
    }
    
    // Выбор первого файла
    std::string file1, file2;
    int choice;
    
    std::cout << "\nВыберите номер первого файла: ";
    std::cin >> choice;
    
    if (choice < 1 || choice > files.size()) {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }
    file1 = files[choice - 1];
    
    // Выбор второго файла (нельзя выбрать тот же самый)
    std::cout << "\nВыберите номер второго файла (не " << file1 << "): ";
    std::cin >> choice;
    
    if (choice < 1 || choice > files.size() || files[choice - 1] == file1) {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }
    file2 = files[choice - 1];
    
    std::cout << "\n✓ Выбраны файлы:\n";
    std::cout << "  1. " << file1 << "\n";
    std::cout << "  2. " << file2 << std::endl;



    //std::string fluentFile1 = "Ansys_Fluent_Simulation_Report_sort2.pdf";
    //std::string fluentFile2 = "Ansys_Fluent_Simulation_Report3.pdf";

    std::shared_ptr<AnsysReport> aReport1;
    std::shared_ptr<AnsysReport> aReport2;

    PDFParser parser(file1);
    aReport1 = parser.parse();

    PDFParser parser2(file2);
    aReport2 = parser2.parse();

    std::vector<std::shared_ptr<ReportComposite>> tables1 = aReport1->getTables();
    std::vector<std::shared_ptr<ReportComposite>> tables2 = aReport2->getTables();

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
