#include <iostream>
#include <vector>
#include <cassert>
#include <stdlib.h>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include "XOPlayer.h"

//Кохновец Роман Николаевич, группа РИ-280003
//задача - написать программу, которая играет с пользователем в крестики-нолики

int main()
{
    setlocale(LC_ALL, "ru");
    TreeNode* tn = new TreeNode();
    cout << "Происходит обход дерева...";
    auto res = tn->TreeTraversal();
    //tn->printStatsForEachChoice();
    XOPlayer game(tn);
    game.PlayTicTacToe();
}