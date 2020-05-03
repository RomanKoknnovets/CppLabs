#pragma once
#ifndef PLAYFIELD_H
#define PLAYFIELD_H

constexpr int fieldSize = 3;
constexpr int index(int y, int x) { return y * fieldSize + x; }

struct PlayField
{
public:
    struct CellIdx
    {
    public:
        CellIdx(int y, int x);
        int getX() const { return x; }
        int getY() const { return y; }
        void setX(int X);
        void setY(int Y);
    private:
        int x;
        int y;
    };

    enum class CellState { csEmpty, csCross, csNought };
    enum class FieldState { fsNormal, fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw };
    PlayField() : nextIsCross(true) {}
    CellState operator[](CellIdx index) const;
    FieldState checkFieldStatus() const;
    vector<CellIdx> getEmptyCells() const;
    const PlayField makeMove(CellIdx index) const;
    bool crossIsNext() const { return nextIsCross; }
    void Print() const;
private:
    bool nextIsCross = true;
    vector<CellState> cells = vector<CellState>(fieldSize*fieldSize, CellState::csEmpty);
    PlayField operator+(CellIdx right) const;
};

#endif
