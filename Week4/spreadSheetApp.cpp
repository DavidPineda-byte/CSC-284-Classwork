
#include <iostream>
#include "spreadCell.h"

int main(){

    SpreadCell cell1(1, 1, 10.5);

    cell1.setValue("20.5");
    cout << "Cell value: " << cell1.getValue() << endl;

    


    return 0;
}