#include "TreeNode.h"


bool TreeNode::isTerminal() const
{
    return  playField.checkFieldStatus() == PlayField::mapCondition::fsNormal ? false : true;
}

TreeNode* TreeNode::addChild(PlayField::CellIdx indx)
{
    int curChildCount = childCount(); int possibleChildCount = childQty();
    assert(curChildCount = childCount() < possibleChildCount || curChildCount == possibleChildCount);
    auto childPlayField = *this->value();
    TreeNode* child = new TreeNode(this, childPlayField.makeMove(indx));
    childrens.push_back(child);
    return child;
}

int TreeNode::childCount() const
{
    return childrens.size();
}

const PlayField* TreeNode::value() const
{
    return &playField;
}

int TreeNode::childQty() const
{
    return playField.getEmptyCells().size();
}

TreeNode* TreeNode::GetChild(int childIndex) const
{
    return childrens[childIndex];
}

int TreeNode::GetStatistic(PlayField::cellCondition cond) const
{
    if (cond == PlayField::cellCondition::csCross)
        return crossesWins;
    else return noughtesWins;
}

void TreeNode::ChangeStatistic(int d, PlayField::cellCondition cond)
{
    if (cond == PlayField::cellCondition::csCross)
         crossesWins += d;
    else  noughtesWins += d;
}
