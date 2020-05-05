#include <cassert>
#include "PlayField.h"

using namespace std;


int PlayField::CellIdx::getPosition() const
{
    return  row * sideLength + column;
}

vector<PlayField::CellIdx> PlayField::getEmptyCells() const
{
    vector<CellIdx> emptyCells;
    for (int i = 0; i < sideLength; i++)
        for (int j = 0; j < sideLength; j++)
        {
            if (map[sideLength * i + j] == csEmpty)
            {
                CellIdx cell(i, j);
                emptyCells.push_back(cell);
            }
        }
    return emptyCells;
}

PlayField::mapCondition PlayField::checkFieldStatus() const
{
    for (int k = 0; k < countCells; k += sideLength)
    {
        if (map[k] == map[k + 1]
            && map[k] == map[k + 2])
        {
            if (map[k] == csCross)
                return fsCrossesWin;
            if (map[k] == csNought)
                return fsNoughtsWin;
        }
    }

    for (int k = 0; k < sideLength; k++)
    {
        if (map[k] == map[k + sideLength]
            && map[k] == map[k + sideLength * 2])
        {
            if (map[k] == csCross)
                return fsCrossesWin;
            if (map[k] == csNought)
                return fsNoughtsWin;
        }
    }

    if (map[0] == map[centralCellIndex] && map[8] == map[centralCellIndex]
        || map[2] == map[centralCellIndex] && map[6] == map[centralCellIndex])
    {
        if (map[centralCellIndex] == csCross)
            return fsCrossesWin;
        if (map[centralCellIndex] == csNought)
            return fsNoughtsWin;
    }

    for (int i = 0; i < countCells; i++)
    {
        if (map[i] == csEmpty)
            return fsNormal;
    }
    return fsDraw;
}

PlayField PlayField::makeMove(PlayField::CellIdx index) const
{
    assert(this->map[index.getPosition()] == csEmpty );
    return *this + index;
}

PlayField::cellCondition PlayField::getStep() const
{
    int crossCount = 0, noughtCount = 0;
    for (int i = 0; i < countCells; i++) {
        if (map[i] == csCross) {
            crossCount++;
        }
        if (map[i] == csNought) {
            noughtCount++;
        }
    }
    return crossCount > noughtCount ? csNought : csCross;
}