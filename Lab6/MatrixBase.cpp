#include "MatrixBase.h"

int MatrixBase::element(unsigned int i, unsigned int j) const
{
    assert(i < m_size && j < m_size);
    return m_array[index(i, j)];
}

int& MatrixBase::element(unsigned int i, unsigned int j)
{
    assert(i < m_size && j < m_size);
    return m_array[index(i, j)];
}

void MatrixBase::operator*=(int iMult)
{
    for (int i = 0; i < m_size * m_size; i++)
        m_array[i] *= iMult;
}

void MatrixBase::operator+=(const MatrixBase& iAdd)
{
    assert(iAdd.m_size == m_size);
    for (int i = 0; i < m_size * m_size; i++)
        m_array[i] += iAdd.m_array[i];
}

std::ostream& operator<<(std::ostream& stream, const MatrixBase& iMatrix)
{
    for (int i = 0; i < iMatrix.size(); i++)
    {
        for (int j = 0; j < iMatrix.size(); j++)
            stream << " " << iMatrix.element(i, j);
        stream << std::endl;
    }
    return stream;
}
