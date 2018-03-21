#ifndef _NickwideN_Matrix
#define _NickwideN_Matrix
#include<cstring>    //strcmp
#include<cassert>    //assert
#include<iostream>
typedef double T;
class Matrix {
protected:
    unsigned int rowsCnt, colsCnt;
    T** matrix_arr;
private:
    template <typename T1 = const char *, typename T2 = const char *, typename T3 = const char *>
    friend void error_with_exit(T1 p1, T2 p2 = "", T3 p3 = ""); //???????????????????????????????????????????????????????????????????
    template <typename T1 = const char *, typename T2 = const char *, typename T3 = const char *>
    friend void error_without_exit(T1 p1, T2 p2 = "", T3 p3 = ""); //????????????????????????????????????????????????????????????????
public:
    Matrix(const int rowsCnt = 1, const int colsCnt = 1);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();
    Matrix& operator = (const Matrix& other);
    Matrix& operator = (Matrix&& other);
    Matrix& operator += (const Matrix& other);
    Matrix operator + (const Matrix& other) const;
    Matrix& operator -= (const Matrix& other);
    Matrix operator - (const Matrix& other) const;
    Matrix operator - () const;
    Matrix operator + () const;
    Matrix& operator *= (const Matrix& other);
    Matrix& operator *= (const T& coefficient);
    Matrix operator * (const Matrix& other) const;
    Matrix operator * (const T& coefficient) const;
    friend Matrix operator * (const T& coefficient, const Matrix& other);
    friend Matrix trans(const Matrix & matrix);     //transpose
    Matrix minor(const int row, const int col) const;
    T& operator()(int i, int j);
    T operator()(int i, int j) const;
    

    friend std::ostream & operator << (std::ostream & os, const Matrix & matrix);
    friend std::istream & operator >> (std::istream & is, Matrix & matrix);

    friend bool IsConcerted(const Matrix& matrix1, const Matrix& matrix2, const char* key_statement = "multiply");

    int GetrowsCnt() const;
    int GetcolsCnt() const;
    T** Getmatrix_arr() const;
    void SetrowsCnt(int rowsCnt);
    void SetcolsCnt(int colsCnt);
    void Setmatrix_arr(T** matrix_arr);
};

class SquareMatrix : public Matrix {
public:
    SquareMatrix(const int size = 1);
    SquareMatrix(const Matrix& matrix);
    SquareMatrix(Matrix&& matrix);
    SquareMatrix(const SquareMatrix & other);
    SquareMatrix(SquareMatrix&& other);
    SquareMatrix& operator = (const SquareMatrix & other);
    SquareMatrix& operator = (SquareMatrix && other);
    SquareMatrix& operator += (const Matrix& other);
    SquareMatrix operator + (const SquareMatrix& other) const;
    SquareMatrix& operator -= (const SquareMatrix& other);
    SquareMatrix operator - (const SquareMatrix& other) const;
    SquareMatrix operator - () const;
    SquareMatrix operator + () const;
    SquareMatrix& operator *= (const SquareMatrix& other);
    SquareMatrix& operator *= (const T& coefficient);
    SquareMatrix operator * (const SquareMatrix& m) const;
    SquareMatrix operator * (const T& val) const;
    friend SquareMatrix operator * (const T& coefficient, const SquareMatrix& other);
    friend SquareMatrix trans(const SquareMatrix & s_matrix);   //transpose
    SquareMatrix minor(const int row, const int col) const;     //minor
    friend T det(const SquareMatrix & s_matrix);              //determinant
    friend SquareMatrix inv(const SquareMatrix & s_matrix);     //inverse

    friend std::istream & operator >> (std::istream & is, SquareMatrix & s_matrix);

    friend bool IsSquare(const Matrix& matrix);
};
#endif // !NickwideN

//Quations:
//

