#pragma once

#include "SpreadSheetCell.h"
#include <optional>
#include <string>
#include <string_view>

class StringSpreadCell : public SpreadSheetCell {
public:
    StringSpreadCell();

    void set(std::string_view value) override;
    std::string getString() const override;

private:
    std::optional<std::string> value;
};
