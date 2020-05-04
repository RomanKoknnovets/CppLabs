#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include "XOPlayer.h"

XOPlayer::XOPlayer(TreeNode& tree) : tree(tree), currentNode(&tree)
{
    assert(tree.getStatistics());
}

void XOPlayer::selectPlayer(PlayField::CellState sideOfBot)
{
    assert(sideOfBot != PlayField::CellState::csEmpty);
    this->sideOfBot = sideOfBot;
}

void XOPlayer::makeMove(PlayField::CellIdx iCell)
{
    assert(currentNode->value()[iCell] == PlayField::CellState::csEmpty && !currentNode->isTerminal());
    for (int i = 0; i < currentNode->childCount(); i++)
    {
        TreeNode* tn = &currentNode->operator[](i);
        if (tn->value()[iCell] != PlayField::CellState::csEmpty)
        {
            currentNode = tn;
            break;
        }
    }
}

void XOPlayer::makeMove()
{
    bool s1 = currentState().nextIsCross() && sideOfBot == PlayField::CellState::csCross;
    bool s2 = !(currentState().nextIsCross()) && sideOfBot == PlayField::CellState::csNought;
    assert((s1 || s2) && !currentNode->isTerminal());

    TreeNode* bestMove = nullptr;
    int bestScore = -1;
    for(int i = 0; i < currentNode->childCount(); i++)
    {
        TreeNode& tn = currentNode->operator[](i);
        if (tn.isTerminal())
        {
            auto status = tn.value().checkFieldStatus();
            if (sideOfBot == PlayField::CellState::csCross && status == PlayField::FieldState::fsCrossesWin ||
                sideOfBot == PlayField::CellState::csNought && status == PlayField::FieldState::fsNoughtsWin)
            {
                bestMove = &tn;
                break;
            }
        }
        int wins = s1 ? tn.getStatistics()->crossesWin : tn.getStatistics()->noughtsWin;
        if (wins + tn.getStatistics()->draws > bestScore)
        {
            bestScore = tn.getStatistics()->draws + wins;
            bestMove = &tn;
        }
    }
    currentNode = bestMove;
}

PlayField::FieldState XOPlayer::fieldStatus() const
{
    return currentState().checkFieldStatus();
}
