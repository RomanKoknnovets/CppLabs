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
    StatisticsResult& getStatistics();
    TreeNode* getBestChild()
    {
        if (childQty() != 0)
        {
            fillChildren();
            TreeNode* res = new TreeNode();
            StatisticsResult st(current.nextIsCross);
            st.wins = -1;
            for(int i = 0; i < children.size(); i++)
            {
                TreeNode* node = &children[i];
                StatisticsResult nodeStatistics(current.nextIsCross);
                node->collectStatistics(nodeStatistics);
                auto winState = current.nextIsCross ? PlayField::FieldState::fsCrossesWin : PlayField::FieldState::fsNoughtsWin;
                if (node->current.checkFieldStatus() == winState)
                {
                    res = node;
                    break;
                }
                if (nodeStatistics.wins > st.wins)
                {
                    st = nodeStatistics;
                    res = node;
                }
            }
            return res;
        }
        return nullptr;
    }
private:
    void collectStatistics(StatisticsResult& res);
    int childQty() const;
};

#endif

