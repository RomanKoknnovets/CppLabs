#include "TreeNode.h"

TreeNode::~TreeNode()
{
    children.clear();
    delete statistics;
}

bool TreeNode::isTerminal() const
{
    auto status = field.checkFieldStatus();
    return status != PlayField::FieldState::fsNormal && status != PlayField::FieldState::fsInvalid;
}

void TreeNode::addChild(PlayField::CellIdx index)
{
    assert((int)children.size() < childQty());
    children.push_back(new TreeNode(this, index));
}

TreeNode& TreeNode::operator[](int i) const
{
    assert(i < (int)children.size());
    return *children[i];
}

int TreeNode::childCount() const
{
    return children.size();
}

const PlayField& TreeNode::value() const
{
    return field;
}

const StatisticsResult TreeNode::TreeTraversal()
{
    statistics = new StatisticsResult();
    if (isTerminal())
    {
        auto status = field.checkFieldStatus();
        switch (status)
        {
        case PlayField::FieldState::fsCrossesWin:
            statistics->crossesWin++;
            break;
        case PlayField::FieldState::fsNoughtsWin:
            statistics->noughtsWin++;
            break;
        case PlayField::FieldState::fsDraw:
            statistics->draws++;
            break;
        case PlayField::FieldState::fsInvalid:
            assert(0);
            break;
        }
        return *statistics;
    }

    auto ec = field.getEmptyCells();
    if (childQty() > childCount())
        for (PlayField::CellIdx index : ec)
            addChild(index);

    for (TreeNode* tn : children)
    {
        auto tnres = tn->TreeTraversal();
        *statistics += tnres;
    }
    return *statistics;
}

void TreeNode::printStatsForEachChoice() const
{
    cout << "For: " << endl;
    field.Print();
    for (TreeNode* tn : children)
    {
        cout << "On choice: " << endl;
        tn->field.Print();
        tn->statistics->Print();
    }
    cout << "Total: ";
    statistics->Print();
}

int TreeNode::childQty() const
{
    if (parent) return parent->childQty() - 1;
    return field.size() * field.size();
}

StatisticsResult& StatisticsResult::operator+=(const StatisticsResult& ir)
{
    noughtsWin += ir.noughtsWin;
    crossesWin += ir.crossesWin;
    draws += ir.draws;
    return *this;
}

void StatisticsResult::Print() const
{
    cout << " Crosses won: " << crossesWin << "; Draws: " << draws << "; Noughts won: " << noughtsWin << endl;
}
