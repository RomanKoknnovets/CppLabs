#pragma once

struct XOPlayer
{
public:
    XOPlayer(TreeNode& tree);
    void selectPlayer(PlayField::CellState sideOfBot);
    void makeMove(PlayField::CellIdx iCell);
    void makeMove();
    PlayField currentState() const { return currentNode->value(); }
    PlayField::FieldState fieldStatus() const;
private:
    TreeNode& tree;
    TreeNode* currentNode;
    PlayField::CellState sideOfBot = PlayField::CellState::csCross;
};
