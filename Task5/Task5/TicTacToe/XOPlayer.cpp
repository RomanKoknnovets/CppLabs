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
    //��� �������� ����, ��� ������ ���������
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
    //���������������, ��� ������ ������ 2 ���� ������ ����� �������
    //�� ���� ��� �� ����� ������ 2 ���� ������ ��� ����� ������� (������� - ��� �� ���� ������ ���)
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
            //����� ������ ��������� ���������� ������� ���������
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
    cout << "���� �� ������ ������ ����: " << endl;
    node->field.Print();
    cout << "������� ����� " << (node->field.nextIsCross ? "��������" : "������") << endl;
    cout << "��������, �� ������� �� ��������, ��� �� ������ (������� x ��� o): ";
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
        cout << "�� ��������� ����. ������� �� ���������� ��������� � ��� o: ";
    }
    while (!node->isTerminal())
    {
        system("cls");
        cout << "����:" << endl;
        node->field.Print();
        if (botMoves)
            makeMove();
        else
        {
            int y, x;
            cout << "������� ����� ������ � ������� ������ ����: ";
            while (true)
            {
                cin >> y >> x;
                if (x <= node->field.fieldSize && y <= node->field.fieldSize)
                {
                    auto cs = node->field[y - 1][x - 1];
                    if (cs == PlayField::CellState::csEmpty)
                        break;
                }
                cout << "����������� ��� �������������� ������, ������� ��� ���: ";
            }
            makeMove(PlayField::CellIdx(y - 1, x - 1));
        }
        botMoves = !botMoves;
    }
    system("cls");
    cout << "����:" << endl;
    node->field.Print();
    auto status = node->field.checkFieldStatus();
    switch (status)
    {
    case PlayField::FieldState::fsCrossesWin:
        cout << "�������� ��������!" << endl;
        break;
    case PlayField::FieldState::fsNoughtsWin:
        cout << "�������� ������!" << endl;
        break;
    case PlayField::FieldState::fsDraw:
        cout << "�����!" << endl;
        break;
    }
}