#include "SpreadSheetCell.h"
#include <optional>
#include <string_view>
#include <string>

class DoubleSpreadsheetCell : public SpreadSheetCell {

public: 
    void set(double value);
    void set(std::string_view value) override;
    std::string getString() const override;

private:
    std::optional<double> value;

    std::string doubleToString(double value) const;
    double stringToDouble(std::string_view value) const;
};