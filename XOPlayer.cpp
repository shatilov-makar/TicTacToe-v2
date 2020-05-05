#include "XOPlayer.h"
#include <ctime> 
#include <iostream>
#include <thread>


XOPlayer::XOPlayer(TreeNode& tree)
{
    node = &tree;
}

void XOPlayer::selectPlayer(PlayField::cellCondition cell)
{
	if (cell == PlayField::cellCondition::csNought)
        botSymbol = PlayField::cellCondition::csCross;
	else
        botSymbol = PlayField::cellCondition::csNought;
}

void XOPlayer::makeMove(PlayField::CellIdx iCell)
{

	for (int i = 0; i < node->childCount(); i++)
	{
		if (node->value()->operator[](iCell) == PlayField::cellCondition::csEmpty 
			&& node->GetChild(i)->value()->operator[](iCell) != PlayField::cellCondition::csEmpty)
		{
			node = node->GetChild(i);
			return;
		}
	}
}



void XOPlayer::makeMove()
{
	int max = 0;
	int indx = 0;
	for (int i = 0; i < node->childCount(); i++)
	{
		int wins = node->GetChild(i)->GetStatistic(botSymbol);
		if (wins > max)
		{
			max = wins;
			indx = i;
		}
	}
	node = node->GetChild(indx);
}



PlayField XOPlayer::currentState() const
{
	return *node->value();
}

PlayField::mapCondition XOPlayer::fieldStatus()
{
	return node->value()->checkFieldStatus();
}
