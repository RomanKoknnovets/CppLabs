#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"

bool TreeNode::isTerminal() const
{
    auto status = current.checkFieldStatus();
    return status != PlayField::FieldState::fsNotEnd;
}
void TreeNode::addChild(TreeNode child)
{
    assert((int)children.size() < childQty());
    children.push_back(child);
}
TreeNode* TreeNode::operator[](int i)
{
    assert(i < (int)children.size());
    return &children[i];
}
int TreeNode::childCount() const
{
    return children.size();
}
const PlayField* TreeNode::value()
{
    return &current;
}
StatisticsResult& TreeNode::getStatistics()
{
    cout << "For:" << endl;
    current.Print();
    StatisticsResult r(current.nextIsCross);
    StatisticsResult& res = r;
    fillChildren();
    for (TreeNode tn : children)
    {
        StatisticsResult r(current.nextIsCross);
        StatisticsResult& tnres = r;
        tn.collectStatistics(tnres);
        cout << "Choice:" << endl;
        tn.current.Print();
        tnres.Print();
        res += tnres;
    }
    cout << "Total: ";
    res.Print();
    return res;
}
void TreeNode::collectStatistics(StatisticsResult& res)
{
    if (isTerminal())
    {
        auto status = current.checkFieldStatus();
        switch (status)
        {
        case PlayField::FieldState::fsCrossesWin:
            if (res.forCrosses)
                res.wins++;
            else res.losts++;
            break;
        case PlayField::FieldState::fsNoughtsWin:
            if (res.forCrosses)
                res.losts++;
            else res.wins++;
            break;
        case PlayField::FieldState::fsDraw:
            res.draws++;
            break;
        default:
            assert(0);
            break;
        }
        return;
    }

    fillChildren();

    for (TreeNode tn : children)
        tn.collectStatistics(res);
}
void TreeNode::fillChildren()
{
    auto ec = current.getEmptyCells();
    if (childQty() > childCount())
        for (PlayField::CellIdx index : ec)
            addChild(TreeNode(this, index));
}
int TreeNode::childQty() const
{
    return current.getEmptyCells().size();
}

StatisticsResult& StatisticsResult::operator+=(const StatisticsResult& ir)
{
    wins += ir.wins;
    draws += ir.draws;
    losts += ir.losts;
    return *this;
}
void StatisticsResult::Print()
{
    cout << " Wins: " << wins << "; Draws: " << draws << "; Losts: " << losts << endl;
}