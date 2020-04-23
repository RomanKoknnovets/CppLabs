#include <iostream>
#include <vector>
#include <cassert>
#include "Matrix3x3.h"
#include "MatrixXnX.h"
#include "SingleLinkedList.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    Matrix3x3 res = Matrix3x3();
    res.fillRandomElements(-10, 9);
    cout << "Matrix3x3:" << endl;
    res.print();
    cout << "Cуммы: ";
    for (int i = 0; i < 3; i++)
        cout << "Строка " << i+1 << ": "<< res.sumRow(i) << "; ";
    cout << endl;
    for (int i = 0; i < 3; i++)
        cout << "Столбец " << i+1 << ": Минимум: "<< res.minColumn(i) << "; Максимум: " << res.maxColumn(i) << endl;
    cout << "Сумма эл-в главной диагонали: " << res.sumPrincipalDiag() << "; Побочной диагонали: " << res.sumSecondaryDiag() << endl;
    cout << "Произведение эл-в главной диагонали: " << res.productPrincipalDiag() << "; Побочной диагонали: " << res.productSecondaryDiag() << endl << endl;
    //1.2
    MatrixXnX res1(5);
    res1.fillRandomElements(0, 3);
    cout << "MatrixXnX (5x5):" << endl;
    res1.print();
    cout << "Cуммы: ";
    for (int i = 0; i < res1.size; i++)
        cout << "Строка " << i+1 << ": " << res1.sumRow(i) << "; ";
    cout << endl;
    for (int i = 0; i < res1.size; i++)
        cout << "Столбец " << i + 1 << ": Минимум: " << res1.minColumn(i) << "; Максимум: " << res1.maxColumn(i) << endl;
    cout << "Сумма эл-в главной диагонали: " << res1.sumPrincipalDiag() << "; Побочной диагонали: " << res1.sumSecondaryDiag() << endl;
    cout << "Произведение эл-в главной диагонали: " << res1.productPrincipalDiag() << "; Побочной диагонали: " << res1.productSecondaryDiag() << endl << endl;
    //2 и 3
    SingleLinkedList<int> list;
    list.append(1);
    list.append(1);
    list.append(3);
    list.append(1);
    list.append(3);
    cout << "Добавили по порядку числа 1 1 3 1 3, удалили дубликаты";
    list.distinct();
    cout << endl << "Количество элементов: "<< list.count << endl;
    auto node = list.head;
    cout << "Элементы: ";
    while (node)
    {
        cout << node->value << " ";
        node = node->next;
    }
    cout << endl << "Первые два элемента с конца: " << list.elementFromTheEnd(1) << " " << list.elementFromTheEnd(2) << endl << endl;
    SingleLinkedList<int> list1;
    list1.append(1);
    list1.append(2);
    list1.append(3);
    list1.append(5);
    list1.append(4);
    list1.append(1);
    list1.append(2);
    int count = list1.count;
    cout << "Добавили по порядку числа 1 2 3 5 4 1 2; " << endl;
    cout << "Количество элементов: " << count << endl;
    cout << "elementFromTheEnd(1): " << list1.elementFromTheEnd(1) << endl;
    cout << "elementFromTheEnd(2): " << list1.elementFromTheEnd(2) << endl;
    cout << "elementFromTheEnd(3): " << list1.elementFromTheEnd(3) << endl;
    getchar();
}


