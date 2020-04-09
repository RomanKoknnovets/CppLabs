#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"

//Кохновец Роман Николаевич, группа РИ-280003, лабораторная работа номер 4: Крестики-нолики

int main()
{
    //в данном случае создастся пустое поле и посчитается статистика для игрока, чья очередь ходить (т.к. крестики первые, то для игрока за крестиков)
    //выводится статистика для всех возможных первых шагов и в конце общая статистика, где суммируются статистики для всех шагов
    //StatisticsResult res = TreeNode().getStatistics();

    //то же, но для ситуации
    //
    //           - о х
    //           x x o
    //           - о x
    //
    //"-" это ещё оставшиеся пустыми клетки
    cout << endl;
    /*PlayField pf2 = PlayField()
        .makeMove(PlayField::CellIdx(0, 2))
        .makeMove(PlayField::CellIdx(0, 1))
        .makeMove(PlayField::CellIdx(1, 0))
        .makeMove(PlayField::CellIdx(1, 2))
        .makeMove(PlayField::CellIdx(1, 1))
        .makeMove(PlayField::CellIdx(2, 1))
        .makeMove(PlayField::CellIdx(2, 2));
    StatisticsResult res2 = TreeNode(pf2).getStatistics();*/
    PlayField pf2("- o x x x o - o x"); //без пробелов тоже нормально прочитает
    cout << pf2.nextIsCross;
    TreeNode(pf2).getStatistics();
}