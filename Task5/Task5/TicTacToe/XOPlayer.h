#pragma once
#ifndef XOPLAYER_H
#define XOPLAYER_H

struct XOPlayer
{
public:
    XOPlayer(TreeNode& tree);
    void selectPlayer(PlayField::CellState sideOfBot);
    void makeMove(PlayField::CellIdx iCell);
    void makeMove();
    TreeNode* getCurrentNode() { return node; }
    PlayField::FieldState fieldStatus();
private:
    TreeNode* node;
    PlayField::CellState sideOfBot;
};

#endif // !XOPLAYER_H
