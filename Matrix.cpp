#include"Matrix.h"   
#include<cstring>    //strcmp
#include<cassert>    //assert
#include<iostream>


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   error_functions:
template <typename T1, typename T2, typename T3>
void Matrix::error_with_exit(T1 p1, T2 p2, T3 p3) {
    std::cerr << "Error: " << p1 << ":\n" << p2 << '\n' << p3 << '\n';
    getchar();
    std::exit(1);
}

template <typename T1, typename T2, typename T3>
void Matrix::error_without_exit(T1 p1, T2 p2, T3 p3) {
    std::cerr << "Error: " << p1 << ' ' << p2 << ' ' << p3 << '\n';
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Class Matrix:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Constructors, destructor:
Matrix::Matrix(const int rowsCnt, const int colsCnt) {
    this->matrix_arr = new T*[rowsCnt];
    for (int i = 0; i < rowsCnt; ++i) {
        this->matrix_arr[i] = new T[colsCnt];
        for (int j = 0; j < colsCnt; ++j)
            this->matrix_arr[i][j] = 0;
    }
    this->rowsCnt = rowsCnt;
    this->colsCnt = colsCnt;
}

Matrix::Matrix(const Matrix& other) {
    this->matrix_arr = new T*[other.rowsCnt];
    for (int i = 0; i < other.rowsCnt; ++i) {
        this->matrix_arr[i] = new T[other.colsCnt];
        for (int j = 0; j < other.colsCnt; ++j)
            this->matrix_arr[i][j] = other.matrix_arr[i][j];
    }
    this->rowsCnt = other.rowsCnt;
    this->colsCnt = other.colsCnt;
}

Matrix::Matrix(Matrix&& other)
    : matrix_arr(other.matrix_arr), colsCnt(other.colsCnt), rowsCnt(other.rowsCnt){
    other.colsCnt = 0; other.rowsCnt = 0; other.matrix_arr = 0;
}

Matrix::~Matrix() {
    for (int i = 0; i < rowsCnt; ++i) 
        delete[] matrix_arr[i];
    delete[] matrix_arr;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Operators:
Matrix& Matrix::operator = (const Matrix& other) { 
    if (this != &other) {
        if (!(this->colsCnt == other.colsCnt && this->rowsCnt == other.rowsCnt)) {
            for (int i = 0; i < this->rowsCnt; ++i)
                delete[] this->matrix_arr[i];
            delete[] this->matrix_arr;
            this->matrix_arr = new T*[other.rowsCnt];
            for (int i = 0; i < other.rowsCnt; ++i)
                this->matrix_arr[i] = new T[other.colsCnt];
            this->rowsCnt = other.rowsCnt;
            this->colsCnt = other.colsCnt;
        }
        for (int i = 0; i < this->rowsCnt; ++i)
            for (int j = 0; j < this->colsCnt; ++j)

                this->matrix_arr[i][j] = other.matrix_arr[i][j];
    }
    return *this;
}

Matrix& Matrix::operator = (Matrix&& other) {
    for (int i = 0; i < this->rowsCnt; ++i)
        delete[] this->matrix_arr[i];
    delete[] this->matrix_arr;
    this->matrix_arr = other.matrix_arr; 
    this->colsCnt = other.colsCnt;
    this->rowsCnt = other.rowsCnt;
    other.matrix_arr = 0;
    other.colsCnt = 0;
    other.rowsCnt = 0;
    return *this;
}

Matrix& Matrix::operator += (const Matrix& other) { //*this += other
    if (!IsConcerted(*this, other, "addition"))
        error_with_exit("attempt to sum not concerted matrices", *this, other);
    for (int i = 0; i < this->rowsCnt; ++i) 
        for (int j = 0; j < this->colsCnt; ++j)
            this->matrix_arr[i][j] += other.matrix_arr[i][j];
    return *this;
}

Matrix Matrix::operator + (const Matrix& other) const { //new_matrix = *this + other
    //if (!IsConcerted(*this, other, "sum"))
        //error_with_exit("attemtp to sum not concerted matrices");
    Matrix new_matrix(*this);
    new_matrix += other;
    return new_matrix;
}

Matrix& Matrix::operator -= (const Matrix& other) { //*this -= other
    if (!IsConcerted(*this, other, "addition"))
        error_with_exit("attempt to subtract not concerted matrices", *this, other);
    *this += -other;
    return *this;
}

Matrix Matrix::operator - (const Matrix& other) const { //new_matrix = *this - other
    //if (!IsConcerted(*this, other, "sum"))
        //error_with_exit("attemtp to subtract not concerted matrices");
    Matrix new_matrix(*this);
    new_matrix -= other;
    return new_matrix;
}

Matrix Matrix::operator - () const { //new_matrix = -*this
    return *this * (-1);
}

Matrix Matrix::operator + () const { //new_matrix = +*this
    return *this;
}

Matrix& Matrix::operator *=(const Matrix& other) { //*this *= other
    if (!IsConcerted(*this, other, "multiply")) error_without_exit("attempt to multiply not concerted matrices", *this, other);
    Matrix new_matrix(this->rowsCnt, other.colsCnt);
    for (int i = 0; i < new_matrix.rowsCnt; ++i)
        for (int j = 0; j < new_matrix.colsCnt; ++j)
            for (int k = 0; k < this->colsCnt && k < other.rowsCnt; ++ k)
                new_matrix.matrix_arr[i][j] += this->matrix_arr[i][k] * other.matrix_arr[k][j];
    *this = new_matrix;
    return *this;
}

Matrix& Matrix::operator *= (const T& coefficient) { //*this *= coefficient
    for (int i = 0; i < this->rowsCnt; ++i) 
        for (int j = 0; j < this->colsCnt; ++j)
            this->matrix_arr[i][j] *= coefficient;
    return *this;
}

Matrix Matrix::operator *(const Matrix& other) const { //new_matrix = *this * other
    Matrix new_matrix(*this);
    new_matrix *= other;
    return new_matrix;
}

Matrix Matrix::operator *(const T& coefficient) const { //new_matrix = *this * coefficient
    Matrix new_matrix(*this);
    new_matrix *= coefficient;
    return new_matrix;
}

Matrix operator * (const T& coefficient, const Matrix& other){ //new_matrix = coefficient * other
    return other * coefficient;
}

Matrix trans(const Matrix & matrix) { 
    Matrix new_matrix(matrix.colsCnt, matrix.rowsCnt);
    for (int i = 0; i < new_matrix.rowsCnt; ++i) {
        for (int j = 0; j < new_matrix.colsCnt; ++j)
            new_matrix.matrix_arr[i][j] = matrix.matrix_arr[j][i];
    }
    return new_matrix;
}

Matrix Matrix::minor(const int row, const int col) const {
    Matrix new_matrix(this->rowsCnt - 1, this->colsCnt - 1);
    for (int i_this = 0, i_new = 0; i_this < this->rowsCnt; ++i_this, ++i_new) {
        if (i_this == row) ++i_this;
        if (!(i_this < this->rowsCnt)) break;
        for (int j_this = 0, j_new = 0; j_this < this->rowsCnt; ++j_this, ++j_new) {
            if (j_this == col) ++j_this;
            if (!(j_this < this->rowsCnt)) break;
            new_matrix.matrix_arr[i_new][j_new] = this->matrix_arr[i_this][j_this];
        }
    }
    return new_matrix;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Access to index:
T& Matrix::operator()(int i, int j) {
    assert(i < rowsCnt && j < colsCnt);
    return matrix_arr[i][j];
}
T Matrix::operator()(int i, int j)const {
    assert(i < rowsCnt && j < colsCnt);
    return matrix_arr[i][j];
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  operators "<<" and ">>":
std::ostream & operator << (std::ostream & os, const Matrix & matrix) {
    os.precision(6);
    for (int i = 0; i < matrix.rowsCnt; ++i) {
        for (int j = 0; j < matrix.colsCnt; ++j) {
            os << matrix.matrix_arr[i][j] << '\t';
        }
        os << '\n';
    }
    return os;
}

std::istream & operator >> (std::istream & is, Matrix & matrix) {
    int parametr[2];
    while (isspace(is.peek())) is.ignore(1);
    if (is.eof()) goto end_of_function;
    is >> parametr[0];
    while (isspace(is.peek())) is.ignore(1);
    if (is.eof()) goto end_of_function;
    is >> parametr[1];
    if (!(matrix.rowsCnt == parametr[0] && matrix.colsCnt == parametr[1])) {
        Matrix new_matrix(parametr[0], parametr[1]);
        matrix = new_matrix;
    }
    for (int i = 0; i < matrix.rowsCnt; ++i) {
        for (int j = 0; j < matrix.colsCnt; ++j) {
            while (isspace(is.peek())) is.ignore(1);
            if (is.eof()) goto end_of_function;
            is >> matrix.matrix_arr[i][j];
        }
    }
end_of_function:
    return is;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Check functions:
bool IsConcerted(const Matrix& matrix1, const Matrix& matrix2, const char* key_statement) { 
    if (!strcmp(key_statement, "multiply")) {
        return matrix1.colsCnt == matrix2.rowsCnt;
    }
    else if (!strcmp(key_statement, "addition")) {
        return (matrix1.rowsCnt == matrix2.rowsCnt && matrix1.colsCnt == matrix2.colsCnt);
    }
    else
        error_with_exit("key_statement not define. You can use next key_statements: \"multiply\"(default), \"addition\"");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Getters, Setters:
int Matrix::GetrowsCnt() const{
    return this->rowsCnt;
}
int Matrix::GetcolsCnt() const{
    return this->colsCnt;
}
T** Matrix::Getmatrix_arr()const {
    return this->matrix_arr;
}
void Matrix::SetrowsCnt(int rowsCnt) {
    this->rowsCnt = rowsCnt;
}
void Matrix::SetcolsCnt(int colsCnt) {
    this->colsCnt = colsCnt;
}
void Matrix::Setmatrix_arr(T** matrix_arr) {
    this->matrix_arr = matrix_arr;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Class SquareMatrix:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Constructors:
SquareMatrix::SquareMatrix(const int size) : Matrix(size, size) {}

SquareMatrix::SquareMatrix(const Matrix & matrix): Matrix(matrix){
    assert(IsSquare(*this));
}

SquareMatrix::SquareMatrix(Matrix&& matrix) : Matrix(0, 0){
    assert(IsSquare(matrix));
    delete[] this->matrix_arr;
    this->matrix_arr = matrix.Getmatrix_arr();
    this->rowsCnt = matrix.GetrowsCnt();
    this->colsCnt = matrix.GetcolsCnt();
    matrix.Setmatrix_arr(0);
    matrix.SetrowsCnt(0);
    matrix.SetcolsCnt(0);
}

SquareMatrix::SquareMatrix(const SquareMatrix & other) : Matrix(other) {}

SquareMatrix::SquareMatrix(SquareMatrix&& other) : Matrix(0,0) {
    delete[] this->matrix_arr;
    this->matrix_arr = other.matrix_arr;
    this->rowsCnt = other.rowsCnt;
    this->colsCnt = other.colsCnt;
    other.matrix_arr = 0;
    other.rowsCnt = 0;
    other.colsCnt = 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Operators:
SquareMatrix& SquareMatrix::operator = (const SquareMatrix & other) {
    Matrix::operator= (other);
    return *this;
}

SquareMatrix& SquareMatrix::operator = (SquareMatrix && other) {
    for (int i = 0; i < this->rowsCnt; ++i)
        delete[] this->matrix_arr[i];
    delete[] this->matrix_arr;
    this->matrix_arr = other.matrix_arr;
    this->rowsCnt = other.rowsCnt;
    this->colsCnt = other.colsCnt;
    other.matrix_arr = 0;
    other.rowsCnt = 0;
    other.colsCnt = 0;
    return *this;
}

SquareMatrix& SquareMatrix::operator += (const Matrix& other) {
    Matrix::operator+= (other);
    return *this;
}

SquareMatrix SquareMatrix::operator + (const SquareMatrix& other) const {
    SquareMatrix new_s_matrix(Matrix::operator+(other));
    return new_s_matrix;
}

SquareMatrix& SquareMatrix::operator -= (const SquareMatrix& other) {
    Matrix::operator-= (other);
    return *this;
}

SquareMatrix SquareMatrix::operator - (const SquareMatrix& other) const {
    SquareMatrix new_s_matrix(Matrix::operator-(other));
    return new_s_matrix;
}

SquareMatrix SquareMatrix::operator - () const {
    SquareMatrix new_s_matrix(Matrix::operator-());
    return new_s_matrix;
}

SquareMatrix SquareMatrix::operator + () const {
    SquareMatrix new_s_matrix(Matrix::operator+());
    return new_s_matrix;
}

SquareMatrix& SquareMatrix::operator *= (const SquareMatrix& other) {
    Matrix::operator*=(other);
    return *this;
}

SquareMatrix& SquareMatrix::operator *= (const T& coefficient) {
    Matrix::operator*= (coefficient);
    return *this;
}

SquareMatrix SquareMatrix::operator * (const SquareMatrix& other) const {
    SquareMatrix new_s_matrix(Matrix::operator*(other));
    return new_s_matrix;
}

SquareMatrix SquareMatrix::operator * (const T& coefficient) const {
    SquareMatrix new_s_matrix(Matrix::operator*(coefficient));
    return new_s_matrix;
}

SquareMatrix operator * (const T& coefficient, const SquareMatrix& other) {
    return other * coefficient;
}

SquareMatrix trans(const SquareMatrix & matrix) {
    SquareMatrix new_s_matrix(matrix.rowsCnt);
    return trans((Matrix)new_s_matrix);
}

SquareMatrix SquareMatrix::minor(const int row, const int col) const{
    return this->Matrix::minor(row, col);
}

T det(const SquareMatrix & s_matrix){
    if (s_matrix.rowsCnt < 1) error_with_exit("attempt to take determinant from empty square matrix");
    if (s_matrix.rowsCnt == 1)
        return s_matrix.matrix_arr[0][0];
    if (s_matrix.rowsCnt == 2)
        return s_matrix.matrix_arr[0][0] * s_matrix.matrix_arr[1][1] - s_matrix.matrix_arr[0][1] * s_matrix.matrix_arr[1][0];
    else {
        int det_m = 0;
        for (int i = 0; i < s_matrix.rowsCnt; ++i) {
            T addent = det(s_matrix.minor(i, 0)) * s_matrix.matrix_arr[i][0];
            det_m += (i % 2 == 1 ? -addent : addent);
        }
        return det_m;
    }
    return 0;
}

SquareMatrix inv(const SquareMatrix & s_matrix){
    SquareMatrix new_s_matrix(s_matrix.rowsCnt);
    T det_s_matrix = det(s_matrix);
    for (int i = 0; i < new_s_matrix.rowsCnt; ++i) {
        for (int j = 0; j < new_s_matrix.rowsCnt; ++j) {
            T slot = det(s_matrix.minor(i, j)) / det_s_matrix;
            new_s_matrix.matrix_arr[i][j] = ((i + j) % 2 == 1 ? -slot : slot);
        }
    }
    return trans(new_s_matrix);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  operator ">>":
std::istream & operator >> (std::istream & is, SquareMatrix & s_matrix) {
    int size;
    while (isspace(is.peek())) is.ignore(1);
    if (is.eof()) goto end_of_function;
    is >> size;
    if (!(s_matrix.rowsCnt == size && s_matrix.colsCnt == size)) {
        SquareMatrix new_matrix(size);
        s_matrix = new_matrix;
    }
    for (int i = 0; i < s_matrix.rowsCnt; ++i) {
        for (int j = 0; j < s_matrix.colsCnt; ++j) {
            while (isspace(is.peek())) is.ignore(1);
            if (is.eof()) goto end_of_function;
            is >> s_matrix.matrix_arr[i][j];
        }
    }
end_of_function:
    return is;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Check functions:
bool IsSquare(const Matrix& matrix) {
    return matrix.GetrowsCnt() == matrix.GetcolsCnt();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++