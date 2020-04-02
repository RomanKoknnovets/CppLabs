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
int* TreeNode::getStatistics()
{
    auto forWhom = current.nextIsCross ? PlayField::CellState::csCross : PlayField::CellState::csNought;
    int* res = new int[3]{ 0, 0, 0 };
    getStatistics(forWhom, res);
    return res;
}
void TreeNode::getStatistics(PlayField::CellState forWhom, int* res)
{
    bool forCrosses = (forWhom == PlayField::CellState::csCross);

    if (isTerminal())
    {
        auto status = current.checkFieldStatus();
        switch (status)
        {
        case PlayField::FieldState::fsCrossesWin:
        {
            if (forCrosses)
                res[0]++;
            else res[2]++;
            break;
        }
        case PlayField::FieldState::fsNoughtsWin:
        {
            if (forCrosses)
                res[2]++;
            else res[0]++;
            break;
        }
        case PlayField::FieldState::fsDraw:
        {
            res[1]++;
            break;
        }
        default:
            assert(0);
            break;
        }
        return;
    }

    fillChildren();

    for (TreeNode tn : children)
        tn.getStatistics(forWhom, res);
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