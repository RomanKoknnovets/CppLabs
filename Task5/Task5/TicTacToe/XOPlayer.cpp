#include "XOPlayer.h"

using namespace std;

XOPlayer::XOPlayer(TreeNode& tree) : tree(tree), currentNode(&tree)
{
    assert(tree.getStatistics());
}

void XOPlayer::selectPlayer(PlayField::CellState botSide)
{
    assert(sideOfBot != PlayField::CellState::csEmpty);
    sideOfBot = botSide;
}

void XOPlayer::makeMove(PlayField::CellIdx iCell)
{
    auto nextMove = currentState().nextMove();
    for (int i = 0; i < currentNode->childCount(); i++)
    {
        TreeNode* tn = &currentNode->operator[](i);
        if (tn->value()[iCell] == nextMove)
        {
            currentNode = tn;
            break;
        }
    }
}

void XOPlayer::makeMove()
{
    assert(currentState().nextMove() == sideOfBot && !currentState().isTerminal());

    TreeNode* bestMove = nullptr;
    double bestScore = -1;
    for(int i = 0; i < currentNode->childCount(); i++)
    {
        auto& tn = (*currentNode)[i];
        int wins = currentState().nextIsCross() ? tn.getStatistics()->crossesWin : tn.getStatistics()->noughtsWin;
        int total = tn.getStatistics()->crossesWin + tn.getStatistics()->draws + tn.getStatistics()->noughtsWin;
        double score = ((double)(wins + tn.getStatistics()->draws)) / total;
        if (score > bestScore)
        {
            bestScore = score;
            bestMove = &tn;
        }
    }
    currentNode = bestMove;
}

PlayField::FieldState XOPlayer::fieldStatus() const
{
    return currentState().checkFieldStatus();
}
