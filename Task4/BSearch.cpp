#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

//рекурсивный
int BSearch1(int value, int* arr, int left, int right)
{
    int count = right - left + 1;
    int mid = arr[left + count / 2];
    if (count == 1 && mid != value) return -1;
    if (mid == value) return left + count / 2;
    if (value < mid && count != 1)
        return BSearch1(value, arr, left, left + count / 2 - 1);
    if (value > mid && count > 2)
        return BSearch1(value, arr, left + count / 2 + 1, right);
    return -1;
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
        {
            right = left + count / 2 - 1;
            continue;
        }
        if (value > mid&& count > 2)
        {
            left = left + count / 2 + 1;
            continue;
        }
        return -1;
    }
}
