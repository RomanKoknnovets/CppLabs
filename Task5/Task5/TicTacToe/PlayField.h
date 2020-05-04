#pragma once

struct PlayField
{
public:
    enum class CellState { csEmpty, csCross, csNought };
    enum class FieldState { fsNormal, fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw };
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
    bool isTerminal() const { return checkFieldStatus() != FieldState::fsNormal; }

private:
    PlayField operator+(CellIdx right) const;
    static constexpr int index(int y, int x) { return y * fieldSize + x; }
    static constexpr int index(CellIdx& idx) { return index(idx.getY(), idx.getX()); }

    vector<CellState> cells = vector<CellState>(fieldSize*fieldSize, CellState::csEmpty);
    static constexpr int fieldSize = 3;
};
