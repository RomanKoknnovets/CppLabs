#include<iostream>
#include<cassert>
#include<vector>
#include <string>
using namespace std;
#include "PlayField.h"


void PlayField::CellIdx::setX(int X)
{
    assert(X <= MaxIndex && X >= 0);
    x = X;
}
void PlayField::CellIdx::setY(int Y)
{
    assert(Y <= MaxIndex && Y >= 0);
    y = Y;
}
PlayField::CellIdx::CellIdx(int y, int x)
{
    setX(x);
    setY(y);
}

PlayField::CellState PlayField::operator[](CellIdx index) const
{
    return cells[index.getY() * fieldSize + index.getX()];
}
vector<PlayField::CellState> PlayField::operator[](int y) const
{
    assert(y < 3 && y >= 0);
    auto res = vector<CellState>{ cells[y * fieldSize], cells[y * fieldSize + 1], cells[y * fieldSize + MaxIndex] };
    return res;
}
PlayField::PlayField(PlayField pf, CellIdx index)
{
    cells = pf.cells;

    assert(pf[index] == CellState::csEmpty);
    cells[index.getY() * fieldSize + index.getX()] = pf.nextIsCross ? CellState::csCross : CellState::csNought;

    this->nextIsCross = (!pf.nextIsCross);
}
PlayField::PlayField(vector<CellIdx> Crosses, vector<CellIdx> Noughts)
{
    int sizeDifference = Crosses.size() - Noughts.size();
    assert(sizeDifference <= 1 && sizeDifference >= -1);
    nextIsCross = sizeDifference <= 0;
    for (int i = 0; i < Crosses.size(); i++)
        cells[Crosses[i].getX() * fieldSize + Crosses[i].getY()] = CellState::csCross;
    for (int i = 0; i < Noughts.size(); i++)
        cells[Noughts[i].getX() * fieldSize + Noughts[i].getY()] = CellState::csNought;
}
PlayField::PlayField(string field)
{
    int index = 0;
    int crossesCount = 0;
    int noughtsCount = 0;
    for (char c : field)
    {
        switch (c)
        {
        case 'x':
            cells[index] = CellState::csCross;
            crossesCount++;
            index++;
            break;
        case 'o':
            cells[index] = CellState::csNought;
            noughtsCount++;
            index++;
            break;
        case '-':
            index++;
            break;
        }
    }
    int countDifference = crossesCount - noughtsCount;
    assert(countDifference <= 1 && countDifference >= -1);
    nextIsCross = countDifference <= 0;
}
PlayField::FieldState PlayField::checkFieldStatus() const
{
    int tripleCrossesCount = 0;
    int tripleNoughtsCount = 0;
    bool isEmptyCellsExists = false;

    bool firstDiagonal = true;
    bool secondDiagonal = true;
    for (int i = 0; i < fieldSize; i++)
    {
        if (i > 0)
        {
            if (firstDiagonal && cells[(fieldSize + 1) * i] == cells[(fieldSize + 1) * (i - 1)])
            {
                if (i == MaxIndex)
                {
                    auto d = cells[(fieldSize + 1) * i];
                    if (d == CellState::csCross) tripleCrossesCount++;
                    if (d == CellState::csNought) tripleNoughtsCount++;
                }
            }
            else firstDiagonal = false;
            if (secondDiagonal && cells[(fieldSize - 1)*(i + 1)] == cells[(fieldSize - 1)*i])
            {
                if (i == MaxIndex)
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
                if (j == MaxIndex)
                {
                    auto d = cells[i * fieldSize + j];
                    if (d == CellState::csCross) tripleCrossesCount++;
                    if (d == CellState::csNought) tripleNoughtsCount++;
                }
            }
            else horizontal = false;
            if (vertical && cells[j * fieldSize + i] == cells[(j-1) * fieldSize + i])
            {
                if (j == MaxIndex)
                {
                    auto d = cells[j * fieldSize + i];
                    if (d == CellState::csCross) tripleCrossesCount++;
                    if (d == CellState::csNought) tripleNoughtsCount++;
                }
            }
            else vertical = false;
        }
    }
    for (int i = 0; i < fieldSize*fieldSize; i++)
        if (cells[i] == CellState::csEmpty)
        {
            isEmptyCellsExists = true;
            break;
        }
    if ((tripleCrossesCount > 0 && tripleCrossesCount < fieldSize) && tripleNoughtsCount == 0) return FieldState::fsCrossesWin;
    if (tripleCrossesCount == 0 && (tripleNoughtsCount > 0 && tripleNoughtsCount < fieldSize)) return FieldState::fsNoughtsWin;
    if (tripleCrossesCount == 0 && tripleNoughtsCount == 0)
    {
        if (isEmptyCellsExists)
            return FieldState::fsNotEnd;
        return FieldState::fsDraw;
    }
    return FieldState::fsInvalid;
}
vector<PlayField::CellIdx> PlayField::getEmptyCells() const
{
    vector<CellIdx> res = vector<CellIdx>();
    for (int i = 0; i < fieldSize*fieldSize; i++)
    {
        if (cells[i] == CellState::csEmpty) res.push_back(CellIdx(i / fieldSize, i % fieldSize));
    }
    return res;
}
const PlayField PlayField::makeMove(CellIdx index) const
{
    const PlayField pf(*this, index);
    return pf;
}
PlayField PlayField::operator+(CellIdx right) const
{
    PlayField res(*this, right);
    return res;
}
void PlayField::Print() const
{
    for (int i = 0; i < fieldSize; i++)
    {
        for (int j = 0; j < fieldSize; j++)
            switch (cells[i * fieldSize + j])
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