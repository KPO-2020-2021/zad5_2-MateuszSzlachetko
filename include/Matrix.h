#ifndef MATRIX_H
#define MATRIX_H

/** @file 
 *  @brief Matrix template
 */

#include "Vector.h"

/** @class Matrix
 *  @brief Templated Matrix class
 * 
 * Square Matrix of double,int,float type etc.
 *
 * nxn size - (2x2,3x3 etc.)
 */
template <typename T, const int size>
class Matrix
{
private:
    Vector<T, size> Array[size];

public:
    /** @fn  Matrix()
    *   @brief Default constructor
    *   
    *   Each line of Array is filled
    *   with zeros (0).
    */
    Matrix();

    /** @fn  Matrix(const std::initializer_list<Vector<T, size>> &elements)
    *   @brief Vectors constructor
    *   
    *   Each line of Array is filled
    *   with passed Vector of appropriate size.
    */
    Matrix(const std::initializer_list<Vector<T, size>> &elements);

    /** @fn   Matrix(const std::initializer_list<T> &elements)
    *   @brief Numbers constructor
    *   
    *   Each line of Array is filled
    *   with single elements,passed in initializer list.
    * 
    *   Then init list transformed to std::vector
    *   is passed in array loop,applying each value for
    *   specific cell.
    */
    Matrix(const std::initializer_list<T> &elements);

    /** @fn   Vector<T, size> operator*(const Vector<T, size> &v) const
    *   @brief Matrix * Vector 
    *   
    *   Matrix and Vector multiplication.
    * 
    *   Each row of matrix multiplied with passed
    *   
    *   @param v - Vector of appropriate size and type
    * 
    *   Product of such multiplication is a scalar value so then a
    *   
    *   @return Vector
    * 
    *   from these scalars is created and returned.
    * 
    */
    Vector<T, size> operator*(const Vector<T, size> &v) const;

    /** @fn   Matrix<T, size> operator*(const Matrix<T, size> &m) const
    *   @brief Matrix * Matrix
    *   
    *   Matrix and Matrix multiplication.Matrix as a product.
    *   
    *   Classical algorithm of matrix multiplication O(n^3)
    *   
    *   @param m - Matrix of appropriate size and type
    */
    Matrix<T, size> operator*(const Matrix<T, size> &m) const;

    /** @fn std::ostream &operator<<(std::ostream &os, const Matrix<P, _size> &m)
    *   @brief Matrix display
    *   
    *   Each row of matrix(which is actually a Vector)
    *   is outputed in a loop,row by row.
    */
    template <typename P, const int _size>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<P, _size> &m);

    /** @fn bool operator==(const Matrix<P, _size> &m1, const Matrix<P, _size> &m2)
    *   @brief Matrix comparison
    * 
    *  Both values from passed Matrices are checked if they are equal.
    *  
    *  If yes
    *  @return true
    * 
    *  If no
    *  @return false
    */
    template <typename P, const int _size>
    friend bool operator==(const Matrix<P, _size> &m1, const Matrix<P, _size> &m2);

    /** @fn Vector<T, size> operator[](int index) const
    *   @brief Matrix index operator
    * 
    *   Array type of operator.Passing const object,only for reading.
    */
    Vector<T, size> operator[](int index) const; // operator for reading

    /** @fn Vector<T, size> &operator[](int index)
    *   @brief Matrix index operator
    * 
    *   Array type of operator.Passing non-const object,for setting value of specific cell.
    */
    Vector<T, size> &operator[](int index); // operator for setting
};

template <typename T, const int size>
Matrix<T, size>::Matrix()
{
    for (Vector<T, size> &element : Array)
        element = Vector<T, size>();
}

template <typename T, const int size>
Matrix<T, size>::Matrix(const std::initializer_list<Vector<T, size>> &elements)
{
    int index = 0;
    for (Vector<T, size> element : elements)
        Array[index++] = element;
}

template <typename T, const int size>
Matrix<T, size>::Matrix(const std::initializer_list<T> &elements)
{
    int k = 0;
    const std::vector<T> values = {elements}; // to have array[] acces for each element

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            Array[i][j] = values[k];
            k++;
        }
}

template <typename T, const int size>
Vector<T, size> Matrix<T, size>::operator*(const Vector<T, size> &v) const
{
    std::vector<T> list;

    for (int i = 0; i < size; ++i)
    {
        list.push_back(this->Array[i] * v); // Vector * Vector = scalar value
    }

    return (Vector<T, size>({list}));
}

template <typename T, const int size>
Matrix<T, size> Matrix<T, size>::operator*(const Matrix<T, size> &m) const
{
    int i, j, k;
    Matrix<T, size> result;
    for (i = 0; i < size; ++i)
        for (j = 0; j < size; ++j)
            for (k = 0; k < size; ++k)
            {
                result[i][j] += (*this)[i][k] * m[k][j];
            }
    return result;
}

template <typename P, const int _size>
std::ostream &operator<<(std::ostream &os, const Matrix<P, _size> &m)
{
    for (int i = 0; i < _size; ++i)
    {
        os << m.Array[i];
        os << std::endl;
    }

    return os;
}

template <typename P, const int _size>
bool operator==(const Matrix<P, _size> &m1, const Matrix<P, _size> &m2)
{
    for (int i = 0; i < _size; ++i)
    {
        if (!(m1.Array[i] == m2.Array[i]))
            return false;
    }
    return true;
}

template <typename T, const int size>
Vector<T, size> Matrix<T, size>::operator[](int index) const
{
    if (index < 0 || index > size - 1)
        throw std::invalid_argument("Index out of range");
    else
    {
        return Array[index]; // return copy,which let's us only to read the value
    }
}

template <typename T, const int size>
Vector<T, size> &Matrix<T, size>::operator[](int index)
{
    if (index < 0 || index > size - 1)
        throw std::invalid_argument("Index out of range");
    else
    {
        return Array[index]; // return reference,which let's us set the value
    }
}

#endif // MATRIX_H