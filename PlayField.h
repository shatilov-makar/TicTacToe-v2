#pragma once
#include <vector> 

using namespace std;

class PlayField
{
public:
    enum cellCondition { csEmpty, csCross, csNought };
    enum mapCondition { fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw, fsNormal };
    class CellIdx
    {
    public:
        CellIdx() :row(0), column(0) {};
        CellIdx(int row, int column) :row(row), column(column) {};
        int getPosition() const;
        void operator = (const CellIdx& f)
        {
            this->row = f.row;
            this->column = f.column;
        }
    
    private:
        int row;
        int column;
        const int sideLength = 3;
    };

    cellCondition operator [] (CellIdx index) const
    {
        return map[index.getPosition()];
    }
    cellCondition operator () (int row, int column) const
    {
        return map[row * sideLength + column];
    }

    vector<CellIdx> getEmptyCells() const;
    mapCondition checkFieldStatus() const;
    PlayField makeMove(CellIdx) const;

private:
    const int sideLength = 3;
    const  static int countCells = 9;
    const int centralCellIndex = 4;
    cellCondition map[countCells]{ csEmpty, csEmpty, csEmpty, csEmpty, csEmpty, csEmpty, csEmpty, csEmpty, csEmpty };
    PlayField operator+ (CellIdx index) const
    {
        PlayField newField = PlayField(*this);
        newField.map[index.getPosition()] = getStep();
        return newField;
    }
    cellCondition getStep() const;
};
