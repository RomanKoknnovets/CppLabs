#pragma once
#include <iostream>
#include <cassert>
#include <vector>

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
    std::vector<CellIdx> getEmptyCells() const;
    const PlayField makeMove(CellIdx index) const;
    bool nextIsCross() const;
    void Print() const;
    static int size() { return fieldSize; }
    CellState nextMove() const;
    bool isTerminal() const;

private:
    PlayField operator+(CellIdx right) const;
    static constexpr int index(int y, int x) { return y * fieldSize + x; }
    static constexpr int index(CellIdx& idx) { return index(idx.getY(), idx.getX()); }

    std::vector<CellState> cells = std::vector<CellState>(fieldSize*fieldSize, csEmpty);
    static constexpr int fieldSize = 3;
};
