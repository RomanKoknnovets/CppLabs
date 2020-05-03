#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include "XOPlayer.h"

XOPlayer::XOPlayer(TreeNode& tree) : node(&tree)
{
    assert(&tree);
    assert(tree.getStatistics());
}

void XOPlayer::selectPlayer(PlayField::CellState sideOfBot)
{
    assert(sideOfBot != PlayField::CellState::csEmpty);
    this->sideOfBot = sideOfBot;
}

void XOPlayer::makeMove(PlayField::CellIdx iCell)
{
    assert(node->value()[iCell] == PlayField::CellState::csEmpty && !node->isTerminal());
    for (int i = 0; i < node->childCount(); i++)
    {
        TreeNode* tn = &(*node)[i];
        if (tn->value()[iCell] != PlayField::CellState::csEmpty)
        {
            node = tn;
            break;
        }
    }
}

void XOPlayer::makeMove()
{
    bool s1 = node->value().crossIsNext() && sideOfBot == PlayField::CellState::csCross;
    bool s2 = !(node->value().crossIsNext()) && sideOfBot == PlayField::CellState::csNought;
    assert((s1 || s2) && !node->isTerminal());

    TreeNode* bestMove = node;
    int bestScore = -1;
    for(int i = 0; i < node->childCount(); i++)
    {
        TreeNode& tn = (*node)[i];
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
        if (tn.getStatistics()->losts + tn.getStatistics()->draws > bestScore)
        {
            bestScore = tn.getStatistics()->draws + tn.getStatistics()->losts;
            bestMove = &tn;
        }
    }
    node = bestMove;
}

PlayField::FieldState XOPlayer::fieldStatus()
{
    return node->value().checkFieldStatus();
}
