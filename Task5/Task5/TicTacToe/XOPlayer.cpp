#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include "XOPlayer.h"

XOPlayer::XOPlayer(TreeNode* tree) : node(tree)
{
    assert(tree);
    //как проверка того, что дерево заполнено
    assert(tree->statistics);
}
void XOPlayer::selectPlayer(PlayField::CellState sideOfBot)
{
    assert(sideOfBot != PlayField::CellState::csEmpty);
    this->sideOfBot = sideOfBot;
}
void XOPlayer::makeMove(PlayField::CellIdx iCell)
{
    assert(node->field[iCell] == PlayField::CellState::csEmpty && !node->isTerminal());
    auto oldNode = node;
    for (TreeNode* tn : node->children)
        if (tn->field[iCell] != PlayField::CellState::csEmpty)
            node = tn;
    assert(node != oldNode);
}
void XOPlayer::makeMove()
{
    //подразумевается, что нельзя ходить 2 раза подряд одной стороне
    //то есть бот не может ходить 2 раза подряд без смены стороны (сторона - это за кого играет бот)
    bool s1 = node->field.nextIsCross && sideOfBot == PlayField::CellState::csCross;
    bool s2 = !(node->field.nextIsCross) && sideOfBot == PlayField::CellState::csNought;
    assert((s1 || s2) && !node->isTerminal());
    TreeNode* bestMove = node;
    int bestScore = -1;
    for (TreeNode* tn : node->children)
    {
        if (tn->isTerminal())
        {
            auto status = tn->field.checkFieldStatus();
            //решил убрать очевидный недостаток жадного алгоритма
            if (sideOfBot == PlayField::CellState::csCross && status == PlayField::FieldState::fsCrossesWin ||
                sideOfBot == PlayField::CellState::csNought && status == PlayField::FieldState::fsNoughtsWin)
            {
                bestMove = tn;
                break;
            }
        }
        if (tn->statistics->losts + tn->statistics->draws > bestScore)
        {
            bestScore = tn->statistics->draws + tn->statistics->losts;
            bestMove = tn;
        }
    }
    node = bestMove;
}
PlayField::FieldState XOPlayer::fieldStatus()
{
    return node->field.checkFieldStatus();
}
void XOPlayer::PlayTicTacToe()
{
    system("cls");
    cout << "Поле на момент начала игры: " << endl;
    node->field.Print();
    cout << "Первыми ходят " << (node->field.nextIsCross ? "крестики" : "нолики") << endl;
    cout << "Выберите, вы играете за крестики, или за нолики (введите x или o): ";
    bool botMoves = false;
    while (true)
    {
        char c = getchar();
        if (c == 'x')
        {
            selectPlayer(PlayField::CellState::csNought);
            break;
        }
        if (c == 'o')
        {
            selectPlayer(PlayField::CellState::csCross);
            botMoves = true;
            break;
        }
        cout << "Не распознан знак. Введите на английской раскладке х или o: ";
    }
    while (!node->isTerminal())
    {
        system("cls");
        cout << "Поле:" << endl;
        node->field.Print();
        if (botMoves)
            makeMove();
        else
        {
            int y, x;
            cout << "Введите номер строки и столбца вашего хода: ";
            while (true)
            {
                cin >> y >> x;
                if (x <= node->field.fieldSize && y <= node->field.fieldSize)
                {
                    auto cs = node->field[y - 1][x - 1];
                    if (cs == PlayField::CellState::csEmpty)
                        break;
                }
                cout << "Заполненная или несуществующая клетка, введите ещё раз: ";
            }
            makeMove(PlayField::CellIdx(y - 1, x - 1));
        }
        botMoves = !botMoves;
    }
    system("cls");
    cout << "Итог:" << endl;
    node->field.Print();
    auto status = node->field.checkFieldStatus();
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