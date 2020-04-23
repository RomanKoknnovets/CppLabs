#include <iostream>
#include "Matrix3x3.h"
using namespace std;

int Matrix3x3::element(const int i, const int j) const
{
    return data[i * size + j];
}
void Matrix3x3::setElement(const int i, const int j, const int value)
{
    data[i * size + j] = value;
}
void Matrix3x3::fillRandomElements(const int minVal, const int maxVal)
{
    for (int i = 0; i < count; i++)
        data[i] = rand() % (maxVal - minVal + 1) + minVal;
}
int Matrix3x3::sumPrincipalDiag() const
{
    int res = 0;
    for (int i = 0; i < count; i += 4)
        res += data[i];
    return res;
}
int Matrix3x3::sumSecondaryDiag() const
{
    int res = 0;
    for (int i = size - 1; i < count - 1; i += size - 1)
        res += data[i];
    return res;
}
int Matrix3x3::productPrincipalDiag() const
{
    int res = 1;
    for (int i = 0; i < count; i += size + 1)
        res *= data[i];
    return res;
}
int Matrix3x3::productSecondaryDiag() const
{
    int res = 1;
    for (int i = size - 1; i < count - 1; i += size - 1)
        res *= data[i];
    return res;
}
int Matrix3x3::sumRow(const int iRow) const
{
    int res = 0;
    for (int i = 0; i < size; i++)
        res += data[iRow * size + i];
    return res;
}
int Matrix3x3::minColumn(const int iCol) const
{
    int min = data[iCol];
    for (int i = 1; i < size; i++)
        if (data[i * size + iCol] < min) min = data[i * size + iCol];
    return min;
}
int Matrix3x3::maxColumn(const int iCol) const
{
    int max = data[iCol];
    for (int i = 1; i < size; i++)
        if (data[i * size + iCol] > max) max = data[i * size + iCol];
    return max;
}
void Matrix3x3::print() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << data[i * size + j] << " ";
        cout << endl;
    }
}