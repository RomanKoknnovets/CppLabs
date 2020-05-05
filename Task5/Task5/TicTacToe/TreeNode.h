#pragma once
#include "PlayField.h"

struct StatisticsResult
{
    int crossesWin = 0;
    int draws = 0;
    int noughtsWin = 0;
    StatisticsResult() {}
    StatisticsResult& operator+=(const StatisticsResult& ir);
    void Print() const;
};

struct TreeNode
{
    TreeNode() : field(PlayField()) {}
public:
    ~TreeNode();
    bool isTerminal() const;
    void addChild(PlayField::CellIdx index);
    TreeNode& operator[](int i) const;
    int childCount() const;
    const PlayField& value() const;
    void printStatsForEachChoice() const;
    const StatisticsResult TreeTraversal();
    const StatisticsResult* getStatistics() const { return statistics; }
private:
    TreeNode(TreeNode* parent, PlayField::CellIdx index) : parent(parent), field(parent->field.makeMove(index)) {}
    int childQty() const;

    std::vector<TreeNode*> children;
    StatisticsResult* statistics = nullptr;
    TreeNode* parent = nullptr;
    const PlayField field;
};
