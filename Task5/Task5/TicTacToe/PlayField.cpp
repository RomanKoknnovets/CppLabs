#include<iostream>
#include<cassert>
#include<vector>
#include <string>
using namespace std;
#include "PlayField.h"

void PlayField::CellIdx::setX(int X)
{
    assert(X < fieldSize && X >= 0);
    x = X;
}

void PlayField::CellIdx::setY(int Y)
{
    assert(Y < fieldSize && Y >= 0);
    y = Y;
}

PlayField::CellIdx::CellIdx(int y, int x)
{
    setX(x);
    setY(y);
}

PlayField::CellState PlayField::operator[](CellIdx idx) const
{
    return cells[index(idx.getY(), idx.getX())];
}

PlayField::FieldState PlayField::checkFieldStatus() const
{
    int tripleCrossesCount = 0;
    int tripleNoughtsCount = 0;
    bool firstDiagonal = true;
    bool secondDiagonal = true;
    for (int i = 0; i < fieldSize; i++)
    {
        if (i > 0)
        {
            if (firstDiagonal && cells[(fieldSize + 1) * i] == cells[(fieldSize + 1) * (i - 1)])
            {
                if (i == fieldSize - 1)
                {
                    auto d = cells[(fieldSize + 1) * i];
                    if (d == CellState::csCross) tripleCrossesCount++;
                    if (d == CellState::csNought) tripleNoughtsCount++;
                }
            }
            else firstDiagonal = false;
            if (secondDiagonal && cells[(fieldSize - 1)*(i + 1)] == cells[(fieldSize - 1)*i])
            {
                if (i == fieldSize - 1)
                {
                    auto d = cells[(fieldSize - 1) * (i + 1)];
                    if (d == CellState::csCross) tripleCrossesCount++;
                    if (d == CellState::csNought) tripleNoughtsCount++;
                }
            }
            else secondDiagonal = false;
        }
        bool horizontal = true;
        bool vertical = true;
        for (int j = 1; j < fieldSize; j++)
        {
            if (horizontal && cells[i * fieldSize + j] == cells[i * fieldSize + j - 1])
            {
                if (j == fieldSize - 1)
                {
                    auto d = cells[i * fieldSize + j];
                    if (d == CellState::csCross) tripleCrossesCount++;
                    if (d == CellState::csNought) tripleNoughtsCount++;
                }
            }
            else horizontal = false;
            if (vertical && cells[j * fieldSize + i] == cells[(j-1) * fieldSize + i])
            {
                if (j == fieldSize - 1)
                {
                    auto d = cells[j * fieldSize + i];
                    if (d == CellState::csCross) tripleCrossesCount++;
                    if (d == CellState::csNought) tripleNoughtsCount++;
                }
            }
            else vertical = false;
        }
    }
    bool isEmptyCellsExists = false;
    for (int i = 0; i < fieldSize*fieldSize; i++)
        if (cells[i] == CellState::csEmpty)
            isEmptyCellsExists = true;
    if ((tripleCrossesCount > 0 && tripleCrossesCount < fieldSize) && tripleNoughtsCount == 0) return FieldState::fsCrossesWin;
    if (tripleCrossesCount == 0 && (tripleNoughtsCount > 0 && tripleNoughtsCount < fieldSize)) return FieldState::fsNoughtsWin;
    if (tripleCrossesCount == 0 && tripleNoughtsCount == 0)
    {
        if (isEmptyCellsExists)
            return FieldState::fsNormal;
        return FieldState::fsDraw;
    }
    return FieldState::fsInvalid;
}

vector<PlayField::CellIdx> PlayField::getEmptyCells() const
{
    vector<CellIdx> res = vector<CellIdx>();
    for (int i = 0; i < fieldSize*fieldSize; i++)
        if (cells[i] == CellState::csEmpty) res.push_back(CellIdx(i / fieldSize, i % fieldSize));
    return res;
}

const PlayField PlayField::makeMove(CellIdx index) const
{
    return *this + index;
}

PlayField PlayField::operator+(CellIdx right) const
{
    PlayField pf;
    pf.nextIsCross = !nextIsCross;
    pf.cells = cells;
    assert(pf[right] == CellState::csEmpty);
    pf.cells[index(right.getY(), right.getX())] = nextIsCross ? CellState::csCross : CellState::csNought;
    return pf;
}

void PlayField::Print() const
{
    for (int i = 0; i < fieldSize; i++)
    {
        for (int j = 0; j < fieldSize; j++)
            switch (cells[index(i, j)])
            {
            case CellState::csCross:
                cout << " x";
                break;
            case CellState::csNought:
                cout << " o";
                break;
            case CellState::csEmpty:
                cout << " -";
                break;
            }
        cout << endl;
    }
}
