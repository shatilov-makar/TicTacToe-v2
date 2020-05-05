#pragma once
#include "PlayField.h"
#include "TreeNode.h"
#include <iostream>
#include <string>

class XOPlayer
{
public:
	XOPlayer(TreeNode& tree);
	void selectPlayer(PlayField::cellCondition cc);
	void makeMove(PlayField::CellIdx iCell);
	void makeMove();
	PlayField currentState() const;
	PlayField::mapCondition fieldStatus();
private:
	TreeNode* node;
	PlayField::cellCondition botSymbol;
};

