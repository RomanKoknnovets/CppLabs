#include <iostream>
#include <vector>
#include <cassert>
#include <stdlib.h>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"

//Кохновец Роман Николаевич, группа РИ-280003, лабораторная работа 5

void PlayTicTacToe()
{
    cout << "Вы играете за крестики!" << endl;
    TreeNode* tn = new TreeNode();
    while (!(tn->isTerminal()))
    {
        system("cls");
        cout << "Поле:" << endl;
        tn->current.Print();
        int y, x;
        cout << "Введите номер строки и столбца вашего хода: ";
        auto emptyCells = tn->current.getEmptyCells();
        while (true)
        {
            cin >> y >> x;
            if (x <= fieldSize && y <= fieldSize)
            {
                auto cs = tn->current[y - 1][x - 1];
                if (cs == PlayField::CellState::csEmpty)
                    break;
            }
            cout << "Заполненная или несуществующая клетка, введите ещё раз: ";
        }
        tn = new TreeNode(tn, PlayField::CellIdx(y - 1, x - 1));
        if (!tn->isTerminal())
        {
            cout << "Подождите, игра делает свой ход...";
            tn = tn->getBestChild();
        }
        if (tn->isTerminal())
        {
            auto status = tn->current.checkFieldStatus();
            switch (status)
            {
            case PlayField::FieldState::fsCrossesWin:
                cout << "Победили крестики!" << endl;
                break;
            case PlayField::FieldState::fsNoughtsWin:
                cout << "Победили нолики!" << endl;
                break;
            case PlayField::FieldState::fsDraw:
                cout << "Ничья!" << endl;
                break;
            }
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    PlayTicTacToe();
}