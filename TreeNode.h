#pragma once
#include "PlayField.h"
#include <cassert>

class TreeNode
{
public:
    TreeNode(TreeNode* parent, PlayField state) :playField(state), parent(parent),crossesWins(0), noughtesWins(0) {};
    bool isTerminal() const;
    TreeNode* addChild(PlayField::CellIdx);
    int childCount() const;
    const PlayField* value() const;
    TreeNode* GetChild(int childIndex) const;
    int GetStatistic(PlayField::cellCondition cond) const;
    void ChangeStatistic(int d, PlayField::cellCondition cond);
private:
    const PlayField playField;
    const TreeNode* parent;
    int childQty() const;
    vector<TreeNode*> childrens;
    int crossesWins;
    int noughtesWins;
};