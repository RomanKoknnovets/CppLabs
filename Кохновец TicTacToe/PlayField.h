#pragma once
#ifndef PLAYFIELD_H
#define PLAYFIELD_H

struct PlayField
{
public:
    struct CellIdx
    {
    private:
        int x;
        int y;
    public:
        int getX() const { return x; }
        int getY() const { return y; }
        void setX(int X);
        void setY(int Y);
        CellIdx(int y, int x);
    };
    enum class CellState { csEmpty, csCross, csNought };
    //добавил ещё fsNotEnd для случая когда ещё никто не победил и всё в рамках правил, но остались пустые клетки и ещё можно сделать ход
    enum class FieldState { fsNotEnd, fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw };
    bool nextIsCross = true;
    vector<CellState> cells = vector<CellState>(9, CellState::csEmpty);

    CellState operator[](CellIdx index) const;

    vector<CellState> operator[](int y) const;

    PlayField(PlayField pf, CellIdx index);

    PlayField() : cells(vector<CellState>(9, CellState::csEmpty)), nextIsCross(true) {}

    FieldState checkFieldStatus() const;

    vector<CellIdx> getEmptyCells() const;

    const PlayField makeMove(CellIdx index) const;

private:
    PlayField operator+(CellIdx right) const;
};

#endif

