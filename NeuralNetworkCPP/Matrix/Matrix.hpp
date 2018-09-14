//
//  Matrix.hpp
//  NeuralNetworkCPP
//
//  Created by MAC on 9/11/18.
//  Copyright © 2018 Tony Abou Zaidan. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

typedef unsigned long u_long;

#include <cassert>
#include <cmath>
#include <iostream>

class IMatrix{
protected:
    const u_long s_r;
    const u_long s_c;
    const u_long rows;
    const u_long columns;
public:
    IMatrix(u_long _rows, u_long _columns, u_long s_r, u_long s_c) : rows(_rows), columns(_columns), s_c(s_c), s_r(s_r) {}
    u_long getRowStart(){
        return s_r;
    }
    u_long getRows(){
        return rows - s_r;
    }
    u_long getColumns(){
        return columns - s_c;
    }
    u_long getColumnStart(){
        return s_c;
    }
    virtual void* getElem(u_long, u_long)=0;
};

template <class T>
class Matrix : public IMatrix {
private:
    T** mat;
    Matrix(T***, u_long, u_long, u_long, u_long);
public:
    Matrix(u_long, u_long, bool=false);
    Matrix(T***, u_long, u_long);
    ~Matrix();
    T** getMatrix();
    Matrix& operator + (IMatrix&);
    Matrix& operator - (IMatrix&);
    Matrix& operator * (IMatrix&);
    Matrix& transp();
    Matrix& Extract(u_long, u_long, u_long, u_long);
    void setRow(u_long, T*);
    void print();
    T sumElem();
    void apply(T(*)(T));
    virtual void* getElem(u_long, u_long);
};

template <class T>
Matrix<T>::Matrix(u_long _rows, u_long _columns, bool random) : IMatrix(_rows, _columns, 0, 0)
{
    mat = new T*[rows];
    for(u_long i=0; i<rows; i++)
    {
        mat[i] = new T[columns];
        for(u_long j=0; j<columns; j++)
            mat[i][j] = random ? rand() / double(RAND_MAX) : 0;
    }
}

template <class T>
Matrix<T>::Matrix(T*** _mat, u_long _rows, u_long _columns) : Matrix(_mat, _rows, _columns, 0, 0)
{}

template <class T>
Matrix<T>::Matrix(T*** _mat, u_long _rows, u_long _columns, u_long s_r, u_long s_c) : IMatrix(_rows, _columns, s_r, s_c)
{
    mat = *_mat;
}

template <class T>
Matrix<T>::~Matrix() {
    for(u_long i=0; i<rows; i++)
        delete[] mat[i];
    delete[] mat;
}

template <class T>
T** Matrix<T>::getMatrix()
{
    return mat;
}

template <class T>
Matrix<T>& Matrix<T>::operator+(IMatrix & m2)
{
    assert(m2.getColumns() == getColumns() && m2.getRows() == getRows());
    
    Matrix<T> * m3 = new Matrix(rows, columns);
    for(u_long i=s_r; i<rows; i++)
        for(u_long j=s_c; j<columns; j++)
            m3->mat[i][j] = mat[i][j] + (*(T*)m2.getElem(i, j));
    return *m3;
}

template <class T>
Matrix<T>& Matrix<T>::operator-(IMatrix & m2)
{
    assert(m2.getColumns() == getColumns() && m2.getRows() == getRows());
    
    Matrix<T> * m3 = new Matrix(rows, columns);
    for(u_long i=s_r; i<rows; i++)
        for(u_long j=s_c; j<columns; j++)
            m3->mat[i][j] = mat[i][j] - (*(T*)m2.getElem(i, j));
    return *m3;
}

template <class T>
Matrix<T>& Matrix<T>::operator*(IMatrix& m2)
{
    assert(getColumns() == m2.getRows());
    Matrix<T> * m3 = new Matrix(getRows(), m2.getColumns());
    for(u_long i=0; i<m3->getRows(); i++)
        for(u_long j=0; j<m3->getColumns(); j++)
            for(u_long k=s_c; k<columns; k++)
                m3->mat[i][j] += mat[i+s_r][k+s_c] * (*(T*)m2.getElem(k, j));
    
    return *m3;
}

template <class T>
Matrix<T>& Matrix<T>::transp()
{
    Matrix<T> * m3 = new Matrix(columns, rows);
    for(u_long i=s_r; i<rows; i++)
        for(u_long j=s_c; j<columns; j++)
            m3->mat[j][i] = mat[i][j];
    return *m3;
}

template <class T>
Matrix<T>& Matrix<T>::Extract(u_long s_row, u_long e_row, u_long s_column, u_long e_column)
{
    Matrix<T> * _new = new Matrix(&mat, e_row, e_column, s_row, s_column);
    _new->getRows();
    return *_new;
}

template <class T>
void Matrix<T>::setRow(u_long r, T * row)
{
    for(u_long i=s_c; i<columns; i++)
        mat[r][i] = row[i];
}

template <class T>
void Matrix<T>::print()
{
    for(u_long i=s_r; i<rows; i++)
    {
        for(u_long j=s_c; j<columns; j++)
            std::cout << mat[i][j] << " ";
        std::cout << std::endl;
    }
}

template <class T>
void* Matrix<T>::getElem(u_long i, u_long j) {
    return &mat[i+s_r][j+s_c];
}

template <class T>
void Matrix<T>::apply(T (*func)(T))
{
    for(u_long i=s_r; i<rows; i++)
        for(u_long j=s_c; j<columns; j++)
            mat[i][j] = func(mat[i][j]);
}

template <class T>
T Matrix<T>::sumElem()
{
    T x = 0;
    for(u_long i=s_r; i<rows; i++)
        for(u_long j=s_c; j<columns; j++)
            x += mat[i][j];
    return x;
}

#endif /* Matrix_hpp */
