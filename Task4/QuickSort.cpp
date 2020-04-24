#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

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