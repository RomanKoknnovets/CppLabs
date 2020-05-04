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
    return cells[index(idx)];
}

PlayField::FieldState PlayField::checkFieldStatus() const
{
    vector<CellState> triples;
    bool firstDiagonal = true;
    bool secondDiagonal = true;
    for (int i = 1; i < fieldSize; i++)
    {
        if (firstDiagonal && cells[index(i, i)] == cells[index(i - 1, i - 1)])
        {
            if (i == fieldSize - 1 && cells[index(i, i)] != CellState::csEmpty)
                triples.push_back(cells[index(i, i)]);
        }
        else firstDiagonal = false;
        if (secondDiagonal && cells[index(i, fieldSize - i - 1)] == cells[index(i - 1, fieldSize - i)])
        {
            if (i == fieldSize - 1 && cells[index(i, fieldSize - i - 1)] != CellState::csEmpty)
                triples.push_back(cells[index(i, fieldSize - i - 1)]);
        }
        else secondDiagonal = false;
    }
    for(int i = 0; i < fieldSize; i++)
    {
        bool horizontal = true;
        bool vertical = true;
        for (int j = 1; j < fieldSize; j++)
        {
            if (horizontal && cells[index(i, j)] == cells[index(i, j - 1)])
            {
                if (j == fieldSize - 1 && cells[index(i, j)] != CellState::csEmpty)
                    triples.push_back(cells[index(i, j)]);
            }
            else horizontal = false;
            if (vertical && cells[index(j, i)] == cells[index(j - 1, i)])
            {
                if (j == fieldSize - 1 && cells[index(j, i)] != CellState::csEmpty)
                    triples.push_back(cells[index(j, i)]);
            }
            else vertical = false;
        }
    }
    for (int i = 1; i < triples.size(); i++)
        if (triples[i - 1] != triples[i]) return FieldState::fsInvalid;
    if (triples.size() > 0 && triples.size() < 3)
        if (triples[0] == CellState::csCross)
            return FieldState::fsCrossesWin;
        else return FieldState::fsNoughtsWin;
    if (getEmptyCells().size() == 0) return FieldState::fsDraw;
    return FieldState::fsNormal;
}

vector<PlayField::CellIdx> PlayField::getEmptyCells() const
{
    vector<CellIdx> res = vector<CellIdx>();
    for (int i = 0; i < fieldSize; i++)
        for(int j = 0; j < fieldSize; j++)
            if (cells[index(i,j)] == CellState::csEmpty) res.push_back(CellIdx(i, j));
    return res;
}

const PlayField PlayField::makeMove(CellIdx index) const
{
    return *this + index;
}

PlayField PlayField::operator+(CellIdx right) const
{
    PlayField pf;
    pf.cells = cells;
    assert(pf[right] == CellState::csEmpty);
    pf.cells[index(right)] = nextIsCross() ? CellState::csCross : CellState::csNought;
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
