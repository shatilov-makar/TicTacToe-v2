using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include <iostream>
#include "XOPlayer.h"

const int tranformCharToInt = 48;

void BuildTree(TreeNode& node)
{
    for (int i = 0; i < 9; i++)
    {
        int row = i / 9; int column = i % 9;
        auto condition = node.value()->operator()(row, column);
        if (condition == PlayField::cellCondition::csEmpty)
        {
            auto childNode = node.addChild(PlayField::CellIdx(row, column));
            if (childNode->isTerminal())
            {
                auto fieldStatus = childNode->value()->checkFieldStatus();
                if (fieldStatus == PlayField::mapCondition::fsCrossesWin)
                    childNode->ChangeStatistic(1, PlayField::cellCondition::csCross);
                if (fieldStatus == PlayField::mapCondition::fsNoughtsWin)
                    childNode->ChangeStatistic(1, PlayField::cellCondition::csNought);
                continue;
            }
            BuildTree(*childNode);
        }
    }
    for (int i = 0; i < node.childCount(); i++)
    {
        node.ChangeStatistic(node.GetChild(i)->GetStatistic(PlayField::cellCondition::csCross), PlayField::cellCondition::csCross);
        node.ChangeStatistic(node.GetChild(i)->GetStatistic(PlayField::cellCondition::csNought), PlayField::cellCondition::csNought);
    }
}

void printGameField(const PlayField pf)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (pf(i, j) == PlayField::cellCondition::csCross)
                cout << " X";
            else if (pf(i, j) == PlayField::cellCondition::csNought)
                cout << " O";
            else cout << " -";
        }
        cout << endl;
    }
    cout << endl;
}


void makeUserStep(XOPlayer* pl)
{
    while (true)
    {
        char i, j;
        cout << "Make your next step!" << endl;
        cin >> i >> j;
        int a = (int)i - tranformCharToInt;
        int b = (int)j - tranformCharToInt;
        cin.ignore(100, '\n');
        if (a >= 0 && a <= 2 && b >= 0 && b <= 2)
        {
            if (pl->currentState().operator[](PlayField::CellIdx(a, b)) != PlayField::cellCondition::csEmpty)
            {
                cout << "You can only walk through empty cells!" << endl;
                continue;
            }
            pl->makeMove(PlayField::CellIdx(a, b));
            printGameField(pl->currentState());
            break;
        }
        else
            cout << "Your made an incorrect step!" << endl;
    }
}

void makeBotStep(XOPlayer* pl)
{
    cout << "Bot step..." << endl;
    pl->makeMove();
    printGameField(pl->currentState());
}

void GamePlay(TreeNode& rootNode)
{
    int sel_player;
    char sel;
    while (true)
    {
        cout << "Select player (\'X\' - Xs, \'O\' - Os)" << endl;
        cin >> sel;
        cin.ignore(100, '\n');
        if (sel == 'x' || sel == 'X')
            sel_player = 0;
        else if (sel == 'o' || sel == 'O' || sel =='0')
            sel_player = 1;
        else
        {
            cout << "You made an incorrect choice!" << endl;
            continue;
        }
        break;
    }
    TreeNode& const node = rootNode;
    XOPlayer player(node);
    player.selectPlayer(sel_player == 0 ? PlayField::cellCondition::csCross : PlayField::cellCondition::csNought);
    do
    {
        if (sel_player % 2 == 0)
            makeUserStep(&player);
        else makeBotStep(&player);
        sel_player++;
    } while (player.fieldStatus() == PlayField::fsNormal);
    if (player.fieldStatus() == PlayField::fsCrossesWin)
        cout << "Crosses wins!" << endl;
    else if (player.fieldStatus() == PlayField::fsNoughtsWin)
        cout << "Noughts wins!" << endl;
    else  cout << "Draw!" << endl;
}

int main()
{
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; i++)
        cout << i << " -" << " -" << " -" << endl;
    cout << "Please, wait..." << endl;
    TreeNode rootNode(nullptr, PlayField());
    BuildTree(rootNode);
    GamePlay(rootNode);
    return 0;
}