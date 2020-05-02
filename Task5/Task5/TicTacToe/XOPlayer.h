#pragma once
#ifndef XOPLAYER_H
#define XOPLAYER_H

struct XOPlayer
{
    TreeNode* node;
    PlayField::CellState sideOfBot;
    XOPlayer(TreeNode* tree);
    void selectPlayer(PlayField::CellState sideOfBot);
    void makeMove(PlayField::CellIdx iCell);
    void makeMove();
    PlayField::FieldState fieldStatus();
    void PlayTicTacToe();
};

#endif // !XOPLAYER_H
