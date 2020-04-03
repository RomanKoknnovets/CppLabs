﻿#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
#include "PlayField.h"
#include "TreeNode.h"

//Кохновец Роман Николаевич, группа РИ-280003, лабораторная работа номер 4: Крестики-нолики

int main()
{
    cout << "Hello World!" << endl;

    //в данном случае создастся пустое поле и посчитается статистика для игрока, чья очередь ходить (т.к. крестики первые, то для игрока за крестиков)
    auto res = TreeNode().getStatistics();
    cout << res[0] << " " << res[1] << " " << res[2] << endl; //первое - победы, второе - ничьи, третье - проигрыши

    //можно посмотреть не для пустого поля:
    //в данном случае первый игрок сходил в точку 1 1 крестиком, и считается статистика для второго, который за нолики
    PlayField pf1 = PlayField().makeMove(PlayField::CellIdx(1, 1));
    auto res1 = TreeNode(pf1).getStatistics();
    cout << res1[0] << " " << res1[1] << " " << res1[2] << endl;

    //ситуация   - о х
    //           x x o
    //           - о x
    //"-" это ещё оставшиеся пустыми клетки
    //следующий ход за ноликом и во всех(двух) случаях игрок за нолики проиграет, что можно проверить перебором, а т.к. случая два то перебор незатруднителен
    PlayField pf2 = PlayField()
        .makeMove(PlayField::CellIdx(0, 2))
        .makeMove(PlayField::CellIdx(0, 1))
        .makeMove(PlayField::CellIdx(1, 0))
        .makeMove(PlayField::CellIdx(1, 2))
        .makeMove(PlayField::CellIdx(1, 1))
        .makeMove(PlayField::CellIdx(2, 1))
        .makeMove(PlayField::CellIdx(2, 2));
    auto res2 = TreeNode(pf2).getStatistics();
    cout << res2[0] << " " << res2[1] << " " << res2[2];
    return 0;
}
//Требования
/*
 * Лабораторная работа №4
 *
 * Темы:
 *     классы (конструкторы, методы, перегрузка операторов),
 *     std::vector (работа с динамическими массивами средствами STL),
 *     cassert.
 *
 * ----------------------------------- Формулировка задания: -----------------------------------
 * Написать программу, которая осуществляет полный обход дерева решений
 * для игры "Крестики-нолики" (Tic Tac Toe/Noughts and Crosses).
 * При этом для каждого возможного первого хода определяет количество
 * выигрышных/проигрышных и ничьих окончаний игры и выводит результат в консоль.
 *
 * При разработке программы каждый класс (кроме вложенных) располагается в своей паре файлов *.h и *.cpp
 *
 * ------- Класс игрового поля PlayField -------
 * Описать и использовать класс игрового поля PlayField.
 *  - Внутри класса PlayField определить и использовать public класс индекса клетки CellIdx. Определить для
 * класса CellIdx соответствующие конструкторы, сеттеры, геттеры, по возможности проверять правильность
 * задаваемых данных. Строки и столбцы нумеруются в диапазоне [0, 2].
 *  - Для PlayField дважды перегрузить public оператор[] для чтения ячеек, возвращающий перечислитель:
 *     csEmpty - ячейка пуста;
 *     csCross - в ячейке крестик;
 *     csNought - в ячейке нолик;
 * и принимающий в качестве аргуметов два целочисленных индекса, либо CellIdx. Перечислитель определить
 * внутри PlayField.
 *  - Для PlayField перегрузить private оператор+ постановки очередной пометки (крестика или нолика),
 * принимающий на вход экземпляры CellIdx и возвращающий экзмепляр поля с новым состоянием игры.
 *  - Определить public метод возврата всех пустых индексов клеток, getEmptyCells, возвращающий массив std::vector
 * с элементами типа CellIdx.
 *  - public Метод проверки состояния поля checkFieldStatus, возвращающий перечислитель:
 *     fsInvalid - состояние поля некорректно (т.е. нельзя дойти до такого состояния соблюдая правила);
 *     fsCrossesWin - победили крестики;
 *     fsNoughtsWin - победили нолики;
 *     fsDraw - ничья.
 * Данный перечислитель определить внутри класса PlayField.
 *  - Определить public const метод makeMove, который получает индекс клетки CellIdx и возвращает новое поле со
 * сделанным в данной клетке ходом. Если клетка уже заполнена или поле является состоянием конца игры следует
 * вызвать ошибку программы методом cassert.
 *
 * ------- Класс вершины дерева решений TreeNode -------
 * Описать и использовать класс вершины TreeNode дерева решений, несущий в себе const экземпляр текущего состояния
 * игрового поля PlayField, связи с предком и с потомками.
 *  - Для TreeNode определить необходимые конструкторы.
 *  - Определить public метод isTerminal, проверяющий является ли вершина терминальной.
 *  - Определить private метод childQty, определяющий возможное количество потомков на данном уровне дерева.
 *  - Определить public метод addChild добавления нового потомка. Проверять, что потомков не может быть на данном
 * уровне дерева больше, чем положено, в случае попытки добавления большего числа потомков падать с cassert.
 *  - Перегрузить public оператор[], принимающий на вход целое число и возвращающий ссылку на соответствующего потомка,
 * если он существует. Если нет - падать с cassert.
 *  - определить public метод childCount, возвращающий текущее количество потомков у данной вершины.
 *  - определить public метод value, возвращающий const ссылку на состояние поля PlayField в данной вершине дерева.
 *
 * ------- Основная программа -------
 * Решить поставленную задачу используя выше описанные классы.
 * Требования в классам PlayField и TreeNode являются необходимыми и достаточными для решения.
 * Запрещается расширять классы, если нет необходимости. Основания для расширения
 * обязательно пояснять в комментариях к коду.
 * Порядок вывода данных не регламентируется, но он должен быть читаемым и понятным.
*/