#pragma once
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

struct PlayField
{
public:
    enum CellState { csEmpty, csCross, csNought };
    enum FieldState { fsNormal, fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw };

    struct CellIdx
    {
    public:
        CellIdx(int y, int x);
        int getX() const { return x; }
        int getY() const { return y; }
        void setX(int X);
        void setY(int Y);
    private:
        int x = 0;
        int y = 0;
    };

    PlayField() {}
    CellState operator[](CellIdx index) const;
    FieldState checkFieldStatus() const;
    vector<CellIdx> getEmptyCells() const;
    const PlayField makeMove(CellIdx index) const;
    bool nextIsCross() const
    {
        //if crosses go first
        return getEmptyCells().size() % 2 == 1;
    }
    void Print() const;
    static int size() { return fieldSize; }
    bool isTerminal() const;

private:
    PlayField operator+(CellIdx right) const;
    static constexpr int index(int y, int x) { return y * fieldSize + x; }
    static constexpr int index(CellIdx& idx) { return index(idx.getY(), idx.getX()); }

    vector<CellState> cells = vector<CellState>(fieldSize*fieldSize, CellState::csEmpty);
    static constexpr int fieldSize = 3;
};
