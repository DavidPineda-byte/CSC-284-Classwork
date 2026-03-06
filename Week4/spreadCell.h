#ifndef SPREADCELL_H
#define SPREADCELL_H
#include <string>

using namespace std;

 class SpreadCell{

    private: 
        int row;
        int column;
        double value;
    public:
        SpreadCell(int row, int column, double value);
        SpreadCell();
        int getRow();
        int getColumn();
        double getValue();


        void setRow(int row);
        void setColumn(int column);
        void setValue(string value);
        void setValue(double value);
    

};

#endif

