#include "ParsingStrategy/ParsingNestedTable.h"
#include "Composite/SettingsDataTable.h"

#include "ParsingStrategy/ParsingNestedTable.h"
#include "Composite/SettingsDataTable.h"

void ParsingNestedTable::execute(std::string& line, const std::vector<PdfTextEntry>& entries, int& index, std::shared_ptr<AnsysReport> aReport) const {
    std::stack<std::shared_ptr<ReportComposite>> nestedComponentStack;
    std::stack<double> flags;

    auto root = std::make_shared<ReportComposite>(line);
    nestedComponentStack.push(root); 

    algorithm(nestedComponentStack, flags, line, entries, index);
    while (nestedComponentStack.size() > 1)
    {
        nestedComponentStack.pop();
    }
    
    aReport->addTable(nestedComponentStack.top());
    nestedComponentStack.pop();
    index--;
}

void ParsingNestedTable::algorithm(std::stack<std::shared_ptr<ReportComposite>>& nestedComponentStack, 
    std::stack<double>& flags, std::string& line, const std::vector<PdfTextEntry>& entries, int& index) const {
        
    double eps = 0.01;
    double xCoordOfFirstWord = 0;
    flags.push(entries[index].X);
    index++;
    setSentence(line, entries, index);
    std::shared_ptr<ReportComposite> rComposite = std::make_shared<ReportComposite>(line);
    if(!nestedComponentStack.empty()) nestedComponentStack.top()->add(rComposite);
    nestedComponentStack.push(rComposite);
    //std::cout << nestedComponentStack.top()->getName() + " " + nestedComponentStack.top()->getParent()->getName() << "\n";

    if(entries[index].Text == "") {
        algorithm(nestedComponentStack, flags, line, entries, index);
    } else {
        xCoordOfFirstWord = entries[index].X;
        setSentence(line, entries, index);
        std::string tableName = nestedComponentStack.top()->getName() + " table";

        std::string key;
        std::vector<std::string> value;
        TableDataMap rows;
        
        while (true) {
            key = std::move(line);
            setMapValue(value, entries, index);
            rows.insert({key, value});
            value.clear();

            if(!flags.empty()) {
                if(entries[index].X < flags.top() && entries[index].Text == "") {
                    while(flags.top() > entries[index].X && !flags.empty() && !nestedComponentStack.empty()) {
                        flags.pop();
                        nestedComponentStack.pop();
                    }
                    addComponentChild(tableName, rows, nestedComponentStack, flags);
                    algorithm(nestedComponentStack, flags, line, entries, index);
                    break;
                }

                if(entries[index].X == flags.top() && entries[index].Text == "") {
                    addComponentChild(tableName, rows, nestedComponentStack, flags);
                    algorithm(nestedComponentStack, flags, line, entries, index);
                    break;
                }
                if(entries[index].X > flags.top() + eps && entries[index].Text == "") {
                    algorithm(nestedComponentStack, flags, line, entries, index);
                }

                if(entries[index].X + eps < xCoordOfFirstWord 
                    && entries[index].Y < entries[index - 1].Y && entries[index].Text != "") {
                    addComponentChild(tableName, rows, nestedComponentStack, flags);
                    break;
                }
            }
            
            xCoordOfFirstWord = entries[index].X;
            setSentence(line, entries, index);
        }
    }
}

void ParsingNestedTable::addComponentChild(const std::string tableName, const TableDataMap& rows
    , std::stack<std::shared_ptr<ReportComposite>>& nestedComponentStack, std::stack<double>& flags) const {
    SettingsDataTable table(tableName, rows);
    if(!nestedComponentStack.empty() && !flags.empty()){
        nestedComponentStack.top()->add(std::make_shared<SettingsDataTable>(table));
        nestedComponentStack.pop();
        flags.pop();
    } 
}

bool ParsingNestedTable::checkComponentOfSentence(const PdfTextEntry& prevEntry, const PdfTextEntry& currEntry) const {
    double maxSpaceLength = (currEntry.Length / currEntry.Text.size()) * 11; 
    double spaceLength = currEntry.X - prevEntry.X - prevEntry.Length;
    return spaceLength < maxSpaceLength;
}

void ParsingNestedTable::setMapValue(std::vector<std::string>& value, const std::vector<PdfTextEntry>& entries, int& index) const {
    std::string str = "";
    double xCoordOfFirstValue = entries[index].X;
    do {
        setSentence(str, entries, index);
        value.push_back(str);
    } while(!(entries[index].Y < entries[index - 1].Y) || !(entries[index].X < xCoordOfFirstValue)); 
}