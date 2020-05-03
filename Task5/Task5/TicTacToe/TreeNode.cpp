#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"

bool TreeNode::isTerminal() const
{
    auto status = field.checkFieldStatus();
    return status != PlayField::FieldState::fsNormal;
}

void TreeNode::addChild(TreeNode* child)
{
    assert((int)children.size() < childQty());
    children.push_back(child);
}

TreeNode& TreeNode::operator[](int i)
{
    assert(i < (int)children.size());
    TreeNode& tn = *children[i];
    return tn;
}

int TreeNode::childCount() const
{
    return children.size();
}

const PlayField& TreeNode::value()
{
    return field;
}

StatisticsResult* TreeNode::TreeTraversal()
{
    statistics = new StatisticsResult(field.crossIsNext());
    if (isTerminal())
    {
        auto status = field.checkFieldStatus();
        switch (status)
        {
        case PlayField::FieldState::fsCrossesWin:
            if (field.crossIsNext())
                statistics->wins+=1;
            else
                statistics->losts+=1;
            break;
        case PlayField::FieldState::fsNoughtsWin:
            if (field.crossIsNext())
                statistics->losts+=1;
            else
                statistics->wins+=1;
            break;
        case PlayField::FieldState::fsDraw:
            statistics->draws+=1;
            break;
        }
        return statistics;
    }

    auto ec = field.getEmptyCells();
    if (childQty() > childCount())
        for (PlayField::CellIdx index : ec)
            addChild(new TreeNode(this, index));

    for (TreeNode* tn : children)
    {
        auto tnres = tn->TreeTraversal();
        *statistics += *tnres;
    }
    return statistics;
}

void TreeNode::printStatsForEachChoice() const
{
    cout << "For: " << endl;
    field.Print();
    for (TreeNode* tn : children)
    {
        cout << "On choice: " << endl;
        tn->field.Print();
        StatisticsResult stat(field.crossIsNext());
        stat += *tn->statistics;
        stat.Print();
    }
    cout << "Total: ";
    statistics->Print();
}

int TreeNode::childQty() const
{
    return field.getEmptyCells().size();
}

StatisticsResult& StatisticsResult::operator+=(const StatisticsResult& ir)
{
    if (forCrosses == ir.forCrosses)
    {
        wins += ir.wins;
        losts += ir.losts;
    }
    else
    {
        wins += ir.losts;
        losts += ir.wins;
    }
    draws += ir.draws;
    return *this;
}

void StatisticsResult::Print()
{
    cout << " Wins: " << wins << "; Draws: " << draws << "; Losts: " << losts << endl;
}
