#include<iostream>
#include<cassert>
#include<vector>
using namespace std;
#include "PlayField.h"

void PlayField::CellIdx::setX(int X)
{
    assert(X < 3 && X >= 0);
    x = X;
}
void PlayField::CellIdx::setY(int Y)
{
    assert(Y < 3 && Y >= 0);
    y = Y;
}
PlayField::CellIdx::CellIdx(int y, int x)
{
    setX(x);
    setY(y);
}

PlayField::CellState PlayField::operator[](CellIdx index) const
{
    return cells[index.getY() * 3 + index.getX()];
}
vector<PlayField::CellState> PlayField::operator[](int y) const
{
    assert(y < 3 && y >= 0);
    auto res = vector<CellState>{ cells[y * 3], cells[y * 3 + 1], cells[y * 3 + 2] };
    return res;
}
PlayField::PlayField(PlayField pf, CellIdx index)
{
    cells = pf.cells;

    assert(pf[index] == CellState::csEmpty);
    cells[index.getY() * 3 + index.getX()] = pf.nextIsCross ? CellState::csCross : CellState::csNought;

    this->nextIsCross = (!pf.nextIsCross);
}
PlayField::FieldState PlayField::checkFieldStatus() const
{
    int tripleCrossesCount = 0;
    int tripleNoughtsCount = 0;
    bool isEmptyCellsExists = false;

    for (int i = 0; i < 3; i++)
    {
        //можно было бы обращатьс€ реализованным  индексатором, но это ухудшает производительность
        //(закомментированные строки - с использованием реализованных индексаторов)
        //если их раскомментировать, то программа будет работать примерно в 4 раза медленнее
        //со вторым индексатором operator[](CellIdx) не пробовал, но скорее всего тоже будет ощутимо медленнее, так как придетс€ везде создавать экземпл€ры CellIdx
        if (cells[i * 3] == cells[i * 3 + 1] && cells[i * 3 + 1] == cells[i * 3 + 2])
            //if((*this)[i][0] == (*this)[i][1] && (*this)[i][1] == (*this)[i][2])
        {
            auto d = cells[i * 3];//(*this)[i][0];
            if (d == CellState::csCross) tripleCrossesCount += 1;
            if (d == CellState::csNought) tripleNoughtsCount += 1;
        }
        if (cells[i] == cells[3 + i] && cells[3 + i] == cells[6 + i])
            //if ((*this)[0][i] == (*this)[1][i] && (*this)[1][i] == (*this)[2][i])
        {
            auto d = cells[i];//(*this)[0][i];
            if (d == CellState::csCross) tripleCrossesCount += 1;
            if (d == CellState::csNought) tripleNoughtsCount += 1;
        }
    }
    if (cells[0] == cells[4] && cells[4] == cells[8])
        //if((*this)[0][0] == (*this)[1][1] && (*this)[1][1] == (*this)[2][2])
    {
        auto d = cells[0];//(*this)[0][0];
        if (d == CellState::csCross) tripleCrossesCount += 1;
        if (d == CellState::csNought) tripleNoughtsCount += 1;
    }
    if (cells[2] == cells[4] && cells[4] == cells[6])
        //if ((*this)[0][2] == (*this)[1][1] && (*this)[1][1] == (*this)[2][0])
    {
        auto d = cells[2];//(*this)[0][2];
        if (d == CellState::csCross) tripleCrossesCount += 1;
        if (d == CellState::csNought) tripleNoughtsCount += 1;
    }
    for (int i = 0; i < 9; i++)
        if (cells[i] == CellState::csEmpty)
        {
            isEmptyCellsExists = true;
            break;
        }
    //при честной игре линий из 3х крестиков или 3х ноликов может быть от 0 до 2, если есть больше, то что-то не так.
    if ((tripleCrossesCount > 0 && tripleCrossesCount < 3) && tripleNoughtsCount == 0) return FieldState::fsCrossesWin;
    if (tripleCrossesCount == 0 && (tripleNoughtsCount > 0 && tripleNoughtsCount < 3)) return FieldState::fsNoughtsWin;
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
    for (int i = 0; i < 9; i++)
    {
        if (cells[i] == CellState::csEmpty) res.push_back(CellIdx(i / 3, i % 3));
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