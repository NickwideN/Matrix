# Matrix
Library for work with matrices on language C++.
Library was created for work with numbers (int, float, double).
2 classes are introduced in the library: 
  class Matrix  and class SquareMatrix.
Class SquareMatrix is superclasses for class Matrix.
In the class was added such operator as taking determinant and inverse matrix (matrix^-1).

Functions:
friend Matrix trans(const Matrix & matrix);                     return trunspose matrix
friend double det(const SquareMatrix & s_matrix);               ruturn determinant of matrix (for square matrix)
friend SquareMatrix inv(const SquareMatrix & s_matrix);         return inversed matrix (for square matrix)

Methods:
Matrix minor(const int row, const int col) const;           return matrix without row'th row and col'th column.

Operators:
All operators with matrices are defined. For complete review you can use file "Matrix.h".
