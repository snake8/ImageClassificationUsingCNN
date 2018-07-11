//
//  Matrix.h
//  Matrix
//
//  Created by Daniel Solovich on 9/22/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//






#ifndef Matrix_h
#define Matrix_h

#include "IExceptions.h"
#include <vector>
#include <iostream>
#include <random>


template<typename T>
class Matrix
{
private:
    std::vector<std::vector<T>> m_matrix;
private:
    static Matrix<T> dotProduct(Matrix<T>&, Matrix<T>&);
    static Matrix<T> dot(Matrix<T>&, Matrix<T>&);
    static Matrix<T> matrixsum(Matrix<T>&, Matrix<T>&);
    static Matrix<T> getMatrixSum(Matrix<T>&, Matrix<T>&);
    static Matrix<T> matrixmin(Matrix<T>&, Matrix<T>&);
    static Matrix<T> getMatrixMin(Matrix<T>&, Matrix<T>&);
public:
    Matrix() = default;
    Matrix(size_t, size_t);
    Matrix(const Matrix<T>& mat);
    ~Matrix();
    size_t size1() const;
    size_t size2() const;
    T getMaxValue() const;
    T getMinValue() const;
    size_t getStringIndexWithMaxValue() const;
    size_t getStringIndexWithMinValue() const;
    bool isValueInMatrix(const size_t row, const T value) const;
    T getStringWithMaxValue() const;
    T getStringWithMinValue() const;
    T& operator()(const size_t, const size_t);
    std::vector<T> toVector();
public:
    void resizeMatrix(const size_t rows, const size_t columns);
    void resizeMatrix1(const size_t rows);
    void resizeMatrix2(const size_t columns);
    void insertVector(const std::vector<T>& temp);
    void removeRow(const size_t index);
    void operator=(const T value);
    void operator+=(T& matrix);
public:
    static void fillMatrix(Matrix<T> matrix, const size_t from, const size_t to);
    static Matrix<T> transpose(Matrix<double>& mat);
    static Matrix<T> getdot(Matrix<T>&, Matrix<T>&);
    static Matrix<T> sum(Matrix<T>&, Matrix<T>&);
    static Matrix<T> min(Matrix<T>&, Matrix<T>&);
    static void generateRandomMatrixFromMatrix(Matrix<T>&, T, T);
};

// declaration of overloaded functions:
template<typename T>
bool operator==(const Matrix<T>&, const Matrix<T>&);
template<typename T>
Matrix<T> operator*(T, Matrix<T>&);
template<typename T>
bool operator!(const Matrix<T>& mat);
template<typename T>
Matrix<T> operator-(T, Matrix<T>&);
template<typename T>
std::ostream& operator<<(std::ostream&, Matrix<T>&);
template<typename T>
Matrix<T> operator+(T, Matrix<T>&);





template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
    m_matrix.resize(rows);
    for (size_t i = 0; i < m_matrix.size(); i++)
        m_matrix[i].resize(cols);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat)
    : m_matrix(mat.m_matrix) { }

template<typename T>
Matrix<T>::~Matrix() { }

template<typename T>
inline size_t Matrix<T>::size1() const
{
    return m_matrix.size();
}
template<typename T>
inline size_t Matrix<T>::size2() const
{
    return m_matrix.size() == 0 ? 0 : m_matrix[0].size();
}

template<typename T>
inline T get_max_element_in_vector(const std::vector<T>& vec)
{
    auto max_iter_element = std::max_element(vec.begin(), vec.end());
    return vec[std::distance(vec.begin(), max_iter_element)];
}

template<typename T>
inline T Matrix<T>::getMaxValue() const
{
    std::vector<T> maxElementsInEachString;
    for (size_t i = 0; i < m_matrix.size(); i++)
        maxElementsInEachString.push_back(get_max_element_in_vector(m_matrix[i]));
    auto maxIter = std::max_element(maxElementsInEachString.begin(), maxElementsInEachString.end());
    return maxElementsInEachString[std::distance(maxElementsInEachString.begin(), maxIter)];
}

template<typename T>
inline size_t Matrix<T>::getStringIndexWithMaxValue() const
{
    std::vector<T> maxElementsInEachString;
    for (size_t i = 0; i < m_matrix.size(); i++)
        maxElementsInEachString.push_back(get_max_element_in_vector(m_matrix[i]));
    auto maxIter = std::max_element(maxElementsInEachString.begin(), maxElementsInEachString.end());
    return std::distance(maxElementsInEachString.begin(), maxIter);
}

template<typename T>
T get_min_element_in_vector(const std::vector<T>& vec)
{
    auto min_iter_element = std::min_element(vec.begin(), vec.end());
    return vec[std::distance(vec.begin(), min_iter_element)];
}

template<typename T>
T Matrix<T>::getMinValue() const
{
    std::vector<T> minElementsInEachString;
    for (size_t i = 0; i < m_matrix.size(); i++)
        minElementsInEachString.push_back(get_min_element_in_vector(m_matrix[i]));
    auto minIter = std::min_element(minElementsInEachString.begin(), minElementsInEachString.end());
    return minElementsInEachString[std::distance(minElementsInEachString.begin(), minIter)];
}

template<typename T>
size_t Matrix<T>::getStringIndexWithMinValue() const
{
    std::vector<T> minElementsInEachString;
    for (size_t i = 0; i < m_matrix.size(); i++)
        minElementsInEachString.push_back(get_min_element_in_vector(m_matrix[i]));
    auto minIter = std::min_element(minElementsInEachString.begin(), minElementsInEachString.end());
    return std::distance(minElementsInEachString.begin(), minIter);
}

template<typename T>
inline bool binary_search(std::vector<T> data, T target, size_t low, size_t high)
{
    if (low > high) return false;
    size_t mid = (low + high) / 2;
    if (target == data[mid])
        return true;
    else if (target < data[mid])
        return binary_search(data, target, low, mid - 1);
    else
        return binary_search(data, target, mid + 1, high);
}

template<typename T>
inline bool Matrix<T>::isValueInMatrix(const size_t row, const T value) const
{
    std::vector<T> data = m_matrix[row];
    std::sort(data.begin(), data.end());
    return binary_search(data, value, 0, data.size());
}

template<typename T>
void Matrix<T>::resizeMatrix(const size_t rows, const size_t columns)
{
    m_matrix.resize(rows);
    for (size_t i = 0; i < rows; i++)
        m_matrix[i].resize(columns);
}

template<typename T>
void Matrix<T>::resizeMatrix1(const size_t rows)
{
    m_matrix.resize(rows);
}
template<typename T>
inline void Matrix<T>::resizeMatrix2(const size_t columns)
{
    for (size_t i = 0; i < m_matrix.size(); i++)
        m_matrix[i].resize(columns);
}

template<typename T>
inline void Matrix<T>::insertVector(const std::vector<T>& temp)
{
    m_matrix.push_back(temp);
}

template<typename T>
void Matrix<T>::removeRow(const size_t index)
{
    for (size_t i = 0; i < m_matrix.size(); i++)
        m_matrix[i].erase(m_matrix[i].begin() + index);
}

template<typename T>
std::vector<T> Matrix<T>::toVector()
{
    std::vector<T> vec;
    vec.reserve(m_matrix.size() * m_matrix[0].size());
    for (size_t i = 0; i < m_matrix.size(); i++)
    {
        for (size_t j = 0; j < m_matrix[0].size(); j++)
            vec.emplace_back(m_matrix[i][j]);
    }
    return vec;
}

template<typename T>
inline T& Matrix<T>::operator()(const size_t row, const size_t col)
{
    return m_matrix[row][col];
}

template<typename T>
inline void Matrix<T>::operator=(const T value)
{
    for (size_t i = 0; i < m_matrix.size(); i++)
    {
        for (size_t j = 0; j < m_matrix[i].size(); j++)
            m_matrix[i][j] = value;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Matrix<T>& matrix)
{
    for (size_t i = 0; i < matrix.size1(); i++)
    {
        for (size_t j = 0; j < matrix.size2(); j++)
            os << matrix(i, j) << " ";
        std::cout << std::endl;
    }
    std::cout << "Number of rows: " << matrix.size1() << std::endl;
    std::cout << "Number of columns: " << matrix.size2() << std::endl;
    return os;
}

template<typename T>
bool operator==(const Matrix<T>& matrix1, const Matrix<T>& matrix2)
{
    return matrix1.size1() == matrix2.size1() && matrix1.size2() == matrix2.size2() ? true : false;
}

template<typename T>
void Matrix<T>::operator+=(T& value)
{
    for (size_t i = 0; i < m_matrix.size(); i++)
    {
        for (size_t j = 0; j < m_matrix[i].size(); j++)
            m_matrix[i][j] += value;
    }
}


template<typename T>
Matrix<T> Matrix<T>::getdot(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    try
    {
        return Matrix<T>::dotProduct(matrix1, matrix2);
    }
    catch (SizeError& e)
    {
        std::cout << e.backtrace << std::endl;
        std::cout << e.getError() << std::endl;
        exit(1); 
    }
}

template<typename T>
Matrix<T> Matrix<T>::dotProduct(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    return matrix1.size2() == matrix2.size1() ? dot(matrix1, matrix2) : throw SizeError();
}

template<typename T>
Matrix<T> Matrix<T>::dot(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    Matrix<T> resultMatrix = {matrix1.size1(), matrix2.size2()};
    for (size_t i = 0; i < matrix1.size1(); i++)
    {
        for (size_t j = 0; j < matrix2.size2(); j++)
        {
            for (size_t k = 0; k < matrix1.size2(); k++)
                resultMatrix(i, j) += matrix1(i, k) * matrix2(k, j);
        }
    }
    return resultMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::sum(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    try
    {
        return matrixsum(matrix1, matrix2);
    }
    catch (SizeError& e)
    {
        std::cout << e.backtrace << std::endl;
        std::cout << e.getError() << std::endl; 
        exit(1);
    }
}

template<typename T>
Matrix<T> Matrix<T>::matrixsum(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    return matrix1 == matrix2 ? getMatrixSum(matrix1, matrix2) : throw SizeError();
}

template<typename T>
Matrix<T> Matrix<T>::getMatrixSum(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    Matrix<T> result = {matrix1.size1(), matrix1.size2()};
    for (size_t i = 0; i < result.size1(); i++)
    {
        for (size_t j = 0; j < result.size2(); j++)
            result(i, j) = matrix1(i, j) + matrix2(i, j);
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::min(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    try {
        return matrixmin(matrix1, matrix2);
    } catch (SizeError& e) {
        std::cout << e.backtrace << std::endl;
        std::cout << e.getError() << std::endl;
        exit(1);
    }
}

template<typename T>
inline Matrix<T> Matrix<T>::matrixmin(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    return matrix1 == matrix2 ? getMatrixMin(matrix1, matrix2) : throw SizeError();
}

template<typename T>
Matrix<T> Matrix<T>::getMatrixMin(Matrix<T>& matrix1, Matrix<T>& matrix2)
{
    Matrix<T> result(matrix1.size1(), matrix1.size2());
    for (size_t i = 0; i < result.size1(); i++)
    {
        for (size_t j = 0; j < result.size2(); j++)
            result(i, j)  = matrix1(i, j) - matrix2(i, j);
    }
    return result; 
}

template<typename T>
inline Matrix<T> Matrix<T>::transpose(Matrix<double> &mat)
{
    Matrix<T> transposedMatrix(mat.size2(), mat.size1());
    for (size_t i = 0; i < mat.size1(); i++)
    {
        for (size_t j = 0; j < mat.size2(); j++)
            transposedMatrix(j, i) = mat(i, j);
    }
    return transposedMatrix;
}

template<typename T>
inline Matrix<T> operator*(T value, Matrix<T>& mat)
{
    for (size_t i = 0; i < mat.size1(); i++)
    {
        for (size_t j = 0; j < mat.size2(); j++)
            mat(i, j) *= value;
    }
    return mat;
}


template<typename T>
bool operator!(const Matrix<T>& mat)
{
    return !mat.size1() && !mat.size2() ? true : false; 
}

template<typename T>
Matrix<T> operator+(T value, Matrix<T>& mat)
{
    for (size_t i = 0; i < mat.size1(); i++)
    {
        for (size_t j = 0; j < mat.size2(); j++)
            mat(i, j) += value;
    }
    return mat;
}

template<typename T>
Matrix<T> operator-(T value, Matrix<T>& mat)
{
    for (size_t i = 0; i < mat.size1(); i++)
    {
        for (size_t j = 0; j < mat.size2(); j++)
            mat(i, j) = value - mat(i, j);
    }
    return mat;
}

template<typename T>
void Matrix<T>::generateRandomMatrixFromMatrix(Matrix<T>& matrix, T from, T to)
{
    std::random_device rng;
    std::mt19937 dist(rng());
    for (size_t i = 0; i < matrix.size1(); i++)
    {
        for (size_t j = 0; j < matrix.size2(); j++)
        {
            std::uniform_real_distribution<T> dist(from, to);
            matrix(i, j) = dist(rng);
        }
    }
}


#endif /* Matrix_h */
