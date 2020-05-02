#pragma once
#ifndef PLAYFIELD_H
#define PLAYFIELD_H

//#define fieldSize 3 //field 3x3 => size = 3
//#define MaxIndex (fieldSize-1)

struct PlayField
{
public:
    struct CellIdx
    {
    private:
        int x;
        int y;
        const int fieldSize = 3;
    public:
        int getX() const { return x; }
        int getY() const { return y; }
        void setX(int X);
        void setY(int Y);
        CellIdx(int y, int x);
    };

    enum class CellState { csEmpty, csCross, csNought };

    enum class FieldState { fsNotEnd, fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw };

    bool nextIsCross = true;

    const int fieldSize = 3;

    vector<CellState> cells = vector<CellState>(fieldSize*fieldSize, CellState::csEmpty);

    CellState operator[](CellIdx index) const;

    vector<CellState> operator[](int y) const;

    PlayField(PlayField pf, CellIdx index);

    PlayField() : nextIsCross(true) {}

    PlayField(vector<CellIdx> Crosses, vector<CellIdx> Noughts);

    PlayField(string field);

    FieldState checkFieldStatus() const;

    vector<CellIdx> getEmptyCells() const;

    const PlayField makeMove(CellIdx index) const;

    void Print() const;
private:

    PlayField operator+(CellIdx right) const;
};

#endif

