#include "DoubleSpreadsheetCell.h"
#include <string>
#include <string_view>
#include <stdexcept>

using namespace std;

void DoubleSpreadsheetCell::set(double value) {
    this->value = value;
}

void DoubleSpreadsheetCell::set(string_view value) {
    this->value = stringToDouble(value);
}

string DoubleSpreadsheetCell::getString() const {
    return doubleToString(value.value_or(0.0));
}

string DoubleSpreadsheetCell::doubleToString(double value) const {
    return to_string(value);
}

double DoubleSpreadsheetCell::stringToDouble(string_view value) const {
    try {
        return stod(string(value));
    } catch (const invalid_argument&) {
        return 0.0;
    }
}