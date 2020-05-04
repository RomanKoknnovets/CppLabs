#include <iostream>
#include <vector>
#include <cassert>
#include <stdlib.h>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include "XOPlayer.h"

//Кохновец Роман Николаевич, группа РИ-280003
//задача - написать программу, которая играет с пользователем в крестики-нолики

int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Обход дерева...";
    TreeNode tn = TreeNode();
    auto res = tn.TreeTraversal();
    XOPlayer game(tn);

    system("cls");
    cout << "Поле на момент начала игры: " << endl;
    game.getCurrentNode()->value().Print();
    cout << "Первыми ходят " << (game.getCurrentNode()->value().crossIsNext() ? "крестики" : "нолики") << endl;
    cout << "Выберите, вы играете за крестики, или за нолики (введите x или o): ";
    bool botMoves = false;
    while (true)
    {
        char c = getchar();
        if (c == 'x')
        {
            game.selectPlayer(PlayField::CellState::csNought);
            break;
        }
        if (c == 'o')
        {
            game.selectPlayer(PlayField::CellState::csCross);
            botMoves = true;
            break;
        }
        cout << "Не распознан знак. Введите на английской раскладке х или o: ";
    }
    while (!game.getCurrentNode()->isTerminal())
    {
        system("cls");
        cout << "Поле:" << endl;
        game.getCurrentNode()->value().Print();
        if (botMoves)
            game.makeMove();
        else
        {
            int y, x;
            cout << "Введите номер строки и столбца вашего хода: ";
            while (true)
            {
                cin >> y >> x;
                if (x <= fieldSize && y <= fieldSize)
                    if (game.getCurrentNode()->value()[PlayField::CellIdx(y - 1, x - 1)] == PlayField::CellState::csEmpty)
                        break;
                cout << "Заполненная или несуществующая клетка, введите ещё раз: ";
            }
            game.makeMove(PlayField::CellIdx(y - 1, x - 1));
        }
        botMoves = !botMoves;
    }
    system("cls");
    cout << "Итог:" << endl;
    game.getCurrentNode()->value().Print();
    auto status = game.getCurrentNode()->value().checkFieldStatus();
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
}
