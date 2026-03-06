#include "StringSpreadCell.h"

using namespace std;

StringSpreadCell::StringSpreadCell() = default;

void StringSpreadCell::set(string_view value) {
    this->value = value;
}

string StringSpreadCell::getString() const {
    return value.value_or("");
}