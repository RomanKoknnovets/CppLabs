#pragma once
#include <iostream>
#include <cassert>

struct MatrixBase
{
public:
    unsigned int size() const { return m_size; }
    virtual int element(unsigned int i, unsigned int j) const;
    virtual int& element(unsigned int i, unsigned int j);
    void operator*=(int iMult);
    void operator+=(const MatrixBase& iAdd);
protected:
    MatrixBase(unsigned int iSize) : m_size(iSize), m_array(new int[iSize * iSize]) {}
    ~MatrixBase() { delete[] m_array; }
private:
    int* m_array;
    const unsigned int m_size = 0;
    constexpr int index(unsigned int i, unsigned int j) const { return i * m_size + j; }
};

std::ostream& operator<<(std::ostream& stream, const MatrixBase& iMatrix);