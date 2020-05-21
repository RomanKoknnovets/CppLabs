#include "Matrix2D.h"
#include "Matrix3D.h"
using namespace std;

void fillElements(MatrixBase& iMatrix)
{
    int num = 1;
    for (int i = 0; i < iMatrix.size(); i++)
        for (int j = 0; j < iMatrix.size(); j++)
            iMatrix.element(i, j) = num++;
}

int main()
{
    setlocale(LC_ALL, "russian");

    cout << "Матрицы 2х2:" << endl;
    Matrix2D m2a;
    Matrix2D m2b;

    fillElements(m2a);
    fillElements(m2b);

    cout << "Первая и вторая матрица после заполнения выглядят так:" << endl;
    cout << "Первая:" << endl;
    cout << m2a;
    cout << "Вторая:" << endl;
    cout << m2b;

    cout << "Складывем их, результат: " << endl;
    m2a += m2b;
    cout << m2a;

    cout << "Умножаем получившуюся матрицу на число 3, результат: " << endl;
    m2a *= 3;
    cout << m2a;


    cout << "Матрицы 3х3:" << endl;
    Matrix3D m3a;
    Matrix3D m3b;

    fillElements(m3a);
    fillElements(m3b);

    cout << "Первая и вторая матрица после заполнения выглядят так:" << endl;
    cout << "Первая:" << endl;
    cout << m3a;
    cout << "Вторая:" << endl;
    cout << m3b;

    cout << "Складывем их, результат: " << endl;
    m3a += m3b;
    cout << m3a;

    cout << "Умножаем получившуюся матрицу на число 5, результат: " << endl;
    m3a *= 5;
    cout << m3a;
}
