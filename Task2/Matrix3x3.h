#pragma once
#ifndef MATRIX3X3_H
#define MATRIX3X3_H

struct Matrix3x3
{
    int size = 3;
    int count = 9;
    int data[9];
    Matrix3x3() {}
    int element(const int i, const int j) const;
    void setElement(const int i, const int j, const int value);
    void fillRandomElements(const int minVal, const int maxVal);
    int sumPrincipalDiag() const;
    int sumSecondaryDiag() const;
    int productPrincipalDiag() const;
    int productSecondaryDiag() const;
    int sumRow(const int iRow) const;
    int minColumn(const int iCol) const;
    int maxColumn(const int iCol) const;
    void print() const;
};

#endif // !MATRIX3X3_H

