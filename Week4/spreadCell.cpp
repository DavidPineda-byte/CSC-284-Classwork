#include "spreadCell.h"
#include <iostream>


SpreadCell::SpreadCell(int row, int column, double value){
    this->row = row;
    this->column = column;
    this->value = value;
}

SpreadCell::SpreadCell(){
    this->row = 0;
    this->column = 0;
    this->value = 0.0;
}

int SpreadCell::getRow(){
    return this->row;
}

int SpreadCell::getColumn(){
    return this->column;
}
double SpreadCell::getValue(){
    return this->value;
}

void SpreadCell::setRow(int row){
    this->row = row;
}
void SpreadCell::setColumn(int column){
    this->column = column;
}
void SpreadCell::setValue(string value){
    try{
    this->value = stod(value);
    }
    catch(invalid_argument& e){
        this->value = 0.0;
        cout << "Invalid input for value. Setting to 0.0" << endl;
    }
}
void SpreadCell::setValue(double value){
    this->value = value;
}

