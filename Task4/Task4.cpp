#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>
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
//рекурсивный
void QuickSort1(int* arr, int begin, int end)
{
    int i = begin;
    int j = end;
    int size = end - begin + 1;
    int mid = arr[begin + size / 2];
    while (i <= j)
    {
        while (arr[i] < mid) i++;
        while (arr[j] > mid) j--;
        if (i <= j)
        {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    if (j > begin)
        QuickSort1(arr, begin, j);
    if (i < end)
        QuickSort1(arr, i, end);
}
//не рекурсивный
void QuickSort2(int* arr, int begin, int end)
{
    struct Interval
    {
        int begin, end;
        Interval(int begin, int end) : begin(begin), end(end) {}
    };
    vector<Interval*> intervals(1, new Interval(begin, end));

    while (intervals.size())
    {
        vector<Interval*> newIntervals;
        for (Interval* interval : intervals)
        {
            int i = interval->begin;
            int j = interval->end;
            int size = j - i + 1;
            int mid = arr[i + size / 2];
            while (i <= j)
            {
                while (arr[i] < mid) i++;
                while (arr[j] > mid) j--;
                if (i <= j)
                {
                    int tmp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = tmp;
                    i++;
                    j--;
                }
            }
            if (j > interval->begin)
                newIntervals.push_back(new Interval(interval->begin, j));
            if (i < interval->end)
                newIntervals.push_back(new Interval(i, interval->end));
        }
        intervals = newIntervals;
    }
}
//рекурсивный
int BSearch1(int value, int* arr, int left, int right)
{
    int count = right - left + 1;
    int mid = arr[left + count / 2];
    if (count == 1 && mid != value) return -1;
    if (mid == value) return left + count / 2;
    if (value < mid && count != 1)
        return BSearch1(value, arr, left, left + count / 2 - 1);
    if (value > mid&& count > 2)
        return BSearch1(value, arr, left + count / 2 + 1, right);
}
//не рекурсивный
int BSearch2(int value, int* arr, int left, int right)
{
    while (true)
    {
        int count = right - left + 1;
        int mid = arr[left + count / 2];
        if (count == 1 && mid != value) return -1;
        if (mid == value) return left + count / 2;
        if (value < mid && count != 1)
            right = left + count / 2 - 1;
        if (value > mid&& count > 2)
            left = left + count / 2 + 1;
    }
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