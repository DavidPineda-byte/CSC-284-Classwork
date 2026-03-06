#include <vector>
#include <memory>
#include <iostream>
#include "SpreadSheetCell.h"
#include "StringSpreadCell.h"
#include "DoubleSpreadsheetCell.h"

int main()
{
    std::vector<std::unique_ptr<SpreadSheetCell>> cells;

    auto stringCell = std::make_unique<StringSpreadCell>();
    stringCell->set("Hello");
    cells.push_back(std::move(stringCell));

    auto stringCell2 = std::make_unique<StringSpreadCell>();
    stringCell2->set("29");
    cells.push_back(std::move(stringCell2));

    auto doubleCell = std::make_unique<DoubleSpreadsheetCell>();
    doubleCell->set(3.14);
    cells.push_back(std::move(doubleCell));

    
    for(const auto& cell : cells) {
        std::cout << cell->getString() << std::endl;
    }

    return 0;
}