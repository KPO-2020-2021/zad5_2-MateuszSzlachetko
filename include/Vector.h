#ifndef VECTOR_H
#define VECTOR_H

/** @file 
 *  @brief Vector template
 */

#include <iostream>
#include <initializer_list>
#include <cmath>
#include <vector>

constexpr double MIN_DIFF = 0.0000000001;

/** @class Vector
 *  @brief Templated Vector class
 * 
 * Vector of double,int,float type etc.
 *
 * n size - (1,2,3 etc.)
 */
template <typename T, const int size>
class Vector
{
private:
    T Components[size];

    static int Total;
    static int Actual;

public:
    /** @fn  Vector()
    *   @brief Default constructor
    *   
    *   Each element of Vector is filled
    *   with zero (0).
    */
    Vector();

    /** @fn  ~Vector()
    *   @brief Default destructor
    *   
    *   Decrease actual value of
    */
    ~Vector();

    /** @fn  Vector(const Vector &v)
    *   @brief Copying constructor
    *   
    *   Each element of passed vector is copied to *this vector 
    *   (for Total,actual vector count)
    */
    Vector(const Vector &v);

    /** @fn   Vector(const std::initializer_list<T> &elements)
    *   @brief Numbers constructor
    *   
    *   Each line of Vector is filled
    *   with single elements,passed in initializer list.
    */
    Vector(const std::initializer_list<T> &elements);

    /** @fn    Vector(const std::vector<T> &elements)
    *   @brief Numbers constructor
    *   
    *   Each line of Vector is filled
    *   with single elements,passed in std::vector.
    */
    Vector(const std::vector<T> &elements);

    /** @fn    Vector<T, size> operator+(const Vector<T, size> &v2) const
    *   @brief Vector + Vector
    *   
    *   Overloaded + operator. Sum of two Vectors.
    *   Value of each cell added to analogous cell of second Vector.
    */
    Vector<T, size> operator+(const Vector<T, size> &v2) const;

    /** @fn    Vector<T, size> operator-(const Vector<T, size> &v2) const
    *   @brief Vector - Vector
    *   
    *   Overloaded - operator. Subtracion of two Vectors.
    *   Value of each cell of right Vector subtracted from analogous cell of first Vector.
    */
    Vector<T, size> operator-(const Vector<T, size> &v2) const;

    /** @fn    Vector<T, size> operator/(const double scalar) const
    *   @brief Vector / scalar
    *   
    *   Overloaded / operator. Division of Vector.
    *   Value of each cell of Vector divided by passed scalar value.
    */
    Vector<T, size> operator/(const double scalar) const;

    /** @fn    Vector<T, size> operator*(const T scalar) const
    *   @brief Vector * scalar
    *   
    *   Overloaded * operator. Multiplication of vector and scalar value,scalar (T) value as a product
    *   then returned in a new Vector (one by one list of type T elements).
    */
    Vector<T, size> operator*(const T scalar) const;

    /** @fn    T operator*(const Vector<T, size> &v2) const
    *   @brief Vector * Vector
    *   
    *   Overloaded * operator. Multiplication of two vectors,analogous multiplied cells added
    *   to global result
    *   
    *   @return T -type value sum of all multiplications
    */
    T operator*(const Vector<T, size> &v2) const;
    double Length() const;

    /** @fn bool operator==(const Vector<P, _size> &v1, const Vector<P, _size> &v2)
    *   @brief Vector comparison
    * 
    *  Both values from passed Vectors are checked if they are equal.
    *  
    *  If yes
    *  @return true
    * 
    *  If no
    *  @return false
    * 
    * Minimal difference threshold is applied to ignore thrash values.
    */
    template <typename P, const int _size>
    friend bool operator==(const Vector<P, _size> &v1, const Vector<P, _size> &v2);

    /** @fn std::ostream &operator<<(std::ostream &os, const Vector<P, _size> &v)
    *   @brief Vector display
    *   
    *   Each element of Vector
    *   is outputed in a loop,element by element.
    */
    template <typename P, const int _size>
    friend std::ostream &operator<<(std::ostream &os, const Vector<P, _size> &v);

    /** @fn std::istream &operator>>(std::istream &is, Vector<P, _size> &v)
    *   @brief Vector read
    *   
    *   Each readed element is applied to appropriate cell of vector.
    * 
    *   If value of a wrong type is passed,there will be an error thrown.
    */
    template <typename P, const int _size>
    friend std::istream &operator>>(std::istream &is, Vector<P, _size> &v);

    /** @fn T operator[](int index) const
    *   @brief Vector index operator
    * 
    *   Array type of operator.Passing const object,only for reading.
    */
    T operator[](int index) const;

    /** @fn T &operator[](int index)
    *   @brief Vector index operator
    * 
    *   Array type of operator.Passing non-const object,for setting value of specific element.
    */
    T &operator[](int index);

    /** @fn static int Get_total()
    *   Get Total vector amount
    * 
    */
    static int Get_total() { return Total; };

    /** @fn static int Get_Actual()
    *   Get Actual vector amount
    * 
    */
    static int Get_Actual() { return Actual; };
};

template <typename T, const int size>
Vector<T, size>::Vector(const Vector &v)
{
    Actual++;
    Total++;

    for (int i = 0; i < size; ++i)
        Components[i] = v.Components[i];
}

template <typename T, const int size>
Vector<T, size>::~Vector()
{
    --Actual;
}

template <typename T, const int size>
int Vector<T, size>::Total = 0;

template <typename T, const int size>
int Vector<T, size>::Actual = 0;

template <typename T, const int size>
Vector<T, size>::Vector()
{
    for (T &element : Components) // initialize each element with default value = 0
        element = 0;
    Actual++;
    Total++;
}

template <typename T, const int size>
Vector<T, size>::Vector(const std::initializer_list<T> &elements) //: Vector()
{
    int index = 0;
    for (T element : elements)
        Components[index++] = element;
    Actual++;
    Total++;
}

template <typename T, const int size>
Vector<T, size>::Vector(const std::vector<T> &elements) //: Vector()
{
    int index = 0;
    if (elements.size() > size || elements.size() < size)
        throw std::invalid_argument("Wrong parameters-Vector initialization");
    for (T element : elements)
        Components[index++] = element;
    Actual++;
    Total++;
}

template <typename T, const int size>
Vector<T, size> Vector<T, size>::operator+(const Vector<T, size> &v2) const
{
    Vector<T, size> result;

    for (int i = 0; i < size; ++i)
    {
        result.Components[i] = this->Components[i] + v2.Components[i];
    }
    return result;
}

template <typename T, const int size>
Vector<T, size> Vector<T, size>::operator-(const Vector<T, size> &v2) const
{
    Vector<T, size> result;

    for (int i = 0; i < size; ++i)
    {
        result.Components[i] = this->Components[i] - v2.Components[i];
    }
    return result;
}

template <typename T, const int size>
Vector<T, size> Vector<T, size>::operator/(const double scalar) const
{
    if (scalar == 0)
    {
        throw std::invalid_argument("Divison by 0 exception");
        return (Vector<T, size>());
    }

    Vector<T, size> result;
    for (int i = 0; i < size; ++i)
    {
        result.Components[i] = this->Components[i] / scalar;
    }
    return result;
}

template <typename T, const int size>
Vector<T, size> Vector<T, size>::operator*(const T scalar) const
{
    Vector<T, size> result;
    for (int i = 0; i < size; ++i)
    {
        result.Components[i] = this->Components[i] * scalar;
    }
    return result;
}

template <typename T, const int size>
T Vector<T, size>::operator*(const Vector<T, size> &v2) const
{
    T result = 0;
    for (int i = 0; i < size; ++i)
    {
        result += this->Components[i] * v2.Components[i];
    }
    return result;
}

template <typename T, const int size>
double Vector<T, size>::Length() const
{
    T pre_result = 0;
    double result;

    for (int i = 0; i < size; ++i)
    {
        pre_result += Components[i] * Components[i]; // x*x y*y z*z etc.
    }

    result = sqrt(pre_result);
    return result;
}

template <typename P, const int _size>
bool operator==(const Vector<P, _size> &v1, const Vector<P, _size> &v2)
{
    for (int i = 0; i < _size; ++i)
    {
        if (std::abs(v1.Components[i] - v2.Components[i]) > MIN_DIFF)
            return false;
    }
    return true;
}

template <typename P, const int _size>
std::ostream &operator<<(std::ostream &os, const Vector<P, _size> &v)
{
    int i = 0;

    for (i; i < _size - 1; ++i)
        os << v.Components[i] << "\t"; // separate each element with a tab

    os << v.Components[i]; // last element printed outside of the loop to avoid additional tab e.g. "x "

    return os;
}

template <typename P, const int _size>
std::istream &operator>>(std::istream &is, Vector<P, _size> &v)
{
    for (int i = 0; i < _size; ++i)
    {
        is >> v.Components[i];
        if (is.fail())
        {
            throw std::invalid_argument("Invalid argument passed while reading vector");
            break;
        }
    }
    return is;
}

template <typename T, const int size>
T Vector<T, size>::operator[](int index) const
{
    if (index < 0 || index > size - 1)
        throw std::invalid_argument("Index out of range"); // return copy,which let's us only to read the value
    else
    {
        return Components[index];
    }
}

template <typename T, const int size>
T &Vector<T, size>::operator[](int index)
{
    if (index < 0 || index > size - 1)
        throw std::invalid_argument("Index out of range");
    else
    {
        return Components[index]; // return reference,which let's us set the value
    }
}

#endif //VECTOR_H