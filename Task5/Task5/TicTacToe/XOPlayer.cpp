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
    bool botIsForCrosses = currentState().nextIsCross() && sideOfBot == PlayField::CellState::csCross;
    bool botIsForNoughts = !(currentState().nextIsCross()) && sideOfBot == PlayField::CellState::csNought;
    assert((botIsForCrosses || botIsForNoughts) && !currentNode->isTerminal());

    TreeNode* bestMove = nullptr;
    int bestScore = -1;
    for(int i = 0; i < currentNode->childCount(); i++)
    {
        auto& tn = (*currentNode)[i];
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
        int wins = botIsForCrosses ? tn.getStatistics()->crossesWin : tn.getStatistics()->noughtsWin;
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
