#pragma once
#ifndef TREENODE_H
#define TREENODE_H

struct TreeNode
{
    TreeNode() : current(PlayField()), parent(nullptr) {}
    TreeNode(TreeNode* parent, PlayField::CellIdx index) : parent(parent), current((*parent).current.makeMove(index)) {}
    TreeNode(PlayField pf) : current(pf), parent(nullptr) {}
    TreeNode* parent;
    const PlayField current;
    vector<TreeNode> children = vector<TreeNode>();
    bool isTerminal() const;
    void addChild(TreeNode child);
    TreeNode* operator[](int i);
    int childCount() const;
    const PlayField* value();
    void fillChildren();
    int* getStatistics();
private:
    void getStatistics(PlayField::CellState forWhom, int* res);
    int childQty() const;
};

#endif // !TREENODE_H

