#pragma once
#ifndef TREENODE_H
#define TREENODE_H

struct StatisticsResult
{
    bool forCrosses;
    int wins = 0;
    int draws = 0;
    int losts = 0;
    StatisticsResult(bool forCrosses) : forCrosses(forCrosses) {}
    StatisticsResult& operator+=(const StatisticsResult& ir);
    void Print();
};

struct TreeNode
{
    TreeNode() : field(PlayField()), parent(nullptr) {}
    TreeNode(TreeNode* parent, PlayField::CellIdx index) : parent(parent), field(parent->field.makeMove(index)) {}
    TreeNode(PlayField pf) : field(pf), parent(nullptr) {}
    bool isTerminal() const;
    void addChild(TreeNode* child);
    TreeNode& operator[](int i);
    int childCount() const;
    const PlayField& value();
    void printStatsForEachChoice() const;
    StatisticsResult* TreeTraversal();
    StatisticsResult* getStatistics() const { return statistics; }
private:
    vector<TreeNode*> children = vector<TreeNode*>();
    StatisticsResult* statistics = nullptr;
    TreeNode* parent;
    const PlayField field;
    int childQty() const;
};

#endif

