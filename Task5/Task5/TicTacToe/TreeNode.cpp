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

TreeNode* TreeNode::operator[](int i)
{
    assert(i < (int)children.size());
    return children[i];
}

int TreeNode::childCount() const
{
    return children.size();
}

const PlayField* TreeNode::value()
{
    return &field;
}

StatisticsResult* TreeNode::TreeTraversal()
{
    statistics = new StatisticsResult(field.nextIsCross);
    if (isTerminal())
    {
        auto status = field.checkFieldStatus();
        switch (status)
        {
        case PlayField::FieldState::fsCrossesWin:
            if (field.nextIsCross)
                statistics->wins+=1;
            else
                statistics->losts+=1;
            break;
        case PlayField::FieldState::fsNoughtsWin:
            if (field.nextIsCross)
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

    fillChildren();

    for (TreeNode* tn : children)
    {
        auto tnres = tn->TreeTraversal();
        *statistics += *tnres;
    }
    return statistics;
}

void TreeNode::printStatsForEachChoice()
{
    cout << "Для поля:" << endl;
    field.Print();
    //StatisticsResult r(field.nextIsCross);
    //StatisticsResult& res = r;
    //fillChildren();
    for (TreeNode* tn : children)
    {
        //StatisticsResult r(field.nextIsCross);
        //StatisticsResult& tnres = r;
        //tn->collectStatistics(tnres);
        cout << "При выборе:" << endl;
        tn->field.Print();
        StatisticsResult stat(field.nextIsCross);
        stat += *tn->statistics;
        stat.Print();
        //tnres.Print();
        //res += tnres;
    }
    cout << "Общее кол-во: ";
    statistics->Print();
    //res.Print();
    //return res;
}

void TreeNode::fillChildren()
{
    auto ec = field.getEmptyCells();
    if (childQty() > childCount())
        for (PlayField::CellIdx index : ec)
            addChild(new TreeNode(this, index));
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
    cout << " Побед: " << wins << "; Ничьих: " << draws << "; Поражений: " << losts << endl;
}