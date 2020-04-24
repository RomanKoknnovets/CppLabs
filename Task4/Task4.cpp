#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
#include "QuickSort.h"
#include "BSearch.h"
using namespace std;

void fillRandomElements(int* arr, int begin, int end, int min, int max)
{
    for (int i = begin; i <= end; i++)
        arr[i] = min + rand() % (max - min + 1);
}

int Search(int* arr, int begin, int end, int value)
{
    for (int i = begin; i <= end; i++)
        if (arr[i] == value) return i;
    return -1;
}

int main()
{
    setlocale(LC_ALL, "ru");
    int* arr = new int[100];
    fillRandomElements(arr, 0, 99, -10, 10);
    cout << "До сортировки (первые 50): ";
    for (int i = 0; i < 50; i++)
        cout << arr[i] << " ";
    cout << endl;
    QuickSort1(arr, 0, 99);
    cout << "После сортировки (первые 50): ";
    for (int i = 0; i < 50; i++)
        cout << arr[i] << " ";
    cout << endl;
    int value;
    cout << "Введите значение для бинарного поиска: "; cin >> value;
    int res = BSearch1(value, arr, 0, 99);
    if (res == -1)
        cout << "Значение не найдено" << endl;
    else
        cout << "Полученный индекс: " << res << endl << "Значение по полученному индексу: " << arr[res] << endl;
    delete[] arr;
    cout << endl;
    cout << "Сравнение скорости поиска: " << endl;
    cout << "Создается массив, замеряется общее время поиска в нём элементов методом Search" << endl;
    cout << "Массив сортируется, замеряется общее время поиска в нём элементов методом BSearch" << endl;
    while (true)
    {
        cout << "Новое сравнение" << endl;
        int count;
        int max;
        int triesCount;
        cout << "Введите количество элементов в массиве: "; cin >> count;
        cout << "Диапазон значений: от 0 до "; cin >> max;
        cout << "Сколько раз будет проводиться поиск одного элемента: "; cin >> triesCount;
        arr = new int[count];
        fillRandomElements(arr, 0, count - 1, 0, max);

        auto c11 = clock();
        for (int i = 0; i < count; i++)
            for (int j = 0; j < triesCount; j++)
                auto res1 = Search(arr, 0, count - 1, arr[i]);
        auto c12 = clock();
        auto d1 = c12 - c11;
        cout << "На поиск в неотнортированном массиве обычным поиском ушло тиков: " << d1 << endl;

        cout << "Время на сортировку: ";
        auto c31 = clock();
        QuickSort1(arr, 0, count - 1);
        auto c32 = clock();
        for (int i = 1; i < count; i++)
            assert(arr[i] >= arr[i - 1]);
        cout << c32 - c31 << endl;

        auto c21 = clock();
        for (int i = 0; i < count; i++)
            for (int j = 0; j < triesCount; j++)
                auto res1 = BSearch1(arr[i], arr, 0, count - 1);
        auto c22 = clock();
        auto d2 = c22 - c21;
        cout << "На бинарный поиск в отсортированном массиве ушло тиков: " << d2 << endl << endl;
        delete[] arr;
    }
}