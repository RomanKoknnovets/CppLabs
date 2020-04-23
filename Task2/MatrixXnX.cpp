#include <iostream>
#include "MatrixXnX.h"
using namespace std;

MatrixXnX::MatrixXnX(const int iDim) : size(iDim), data(new int* [iDim]), count(iDim* iDim)
{
    for (int i = 0; i < iDim; i++)
    {
        data[i] = new int[iDim];
        for (int j = 0; j < iDim; j++)
            data[i][j] = 0;
    }
}
MatrixXnX::~MatrixXnX()
{
    for (int i = 0; i < size; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}
int MatrixXnX::element(const int i, const int j) const
{
    return data[i][j];
}
void MatrixXnX::setElement(const int i, const int j, const int value)
{
    data[i][j] = value;
}
void MatrixXnX::fillRandomElements(const int minVal, const int maxVal)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            data[i][j] = rand() % (maxVal - minVal + 1) + minVal;
}
int MatrixXnX::sumPrincipalDiag() const
{
    int res = 0;
    for (int i = 0; i < size; i++)
        res += data[i][i];
    return res;
}
int MatrixXnX::sumSecondaryDiag() const
{
    int res = 0;
    for (int i = 0; i < size; i++)
        res += data[i][size - i - 1];
    return res;
}
int MatrixXnX::productPrincipalDiag() const
{
    int res = 1;
    for (int i = 0; i < size; i++)
        res *= data[i][i];
    return res;
}
int MatrixXnX::productSecondaryDiag() const
{
    int res = 1;
    for (int i = 0; i < size; i++)
        res *= data[i][size - i - 1];
    return res;
}
int MatrixXnX::sumRow(const int iRow) const
{
    int res = 0;
    for (int i = 0; i < size; i++)
        res += data[iRow][i];
    return res;
}
int MatrixXnX::minColumn(const int iCol) const
{
    int min = data[0][iCol];
    for (int i = 1; i < size; i++)
        if (data[i][iCol] < min) min = data[i][iCol];
    return min;
}
int MatrixXnX::maxColumn(const int iCol) const
{
    int max = data[0][iCol];
    for (int i = 1; i < size; i++)
        if (data[i][iCol] > max) max = data[i][iCol];
    return max;
}
void MatrixXnX::print() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << data[i][j] << " ";
        cout << endl;
    }
}