# Matrix
Library for work with matrices in language C++.
Library was created for work with numbers (int, float, double).
2 classes are introduced in the library: 
  class Matrix  and class SquareMatrix.
Class SquareMatrix is a subclasses for class Matrix.
In the class was added such operator as taking determinant and inverse matrix (matrix^-1).

Functions:
friend Matrix trans(const Matrix & matrix);                     return trunspose matrix
friend double det(const SquareMatrix & s_matrix);               ruturn determinant of matrix (for square matrix)
friend SquareMatrix inv(const SquareMatrix & s_matrix);         return inversed matrix (for square matrix)

Methods:
Matrix minor(const int row, const int col) const;           return matrix without row'th row and col'th column.

Operators:
All operators with matrices are defined. For complete review of operators you can use file "Matrix.h".

(Sorry if I maked grammatical mistake)

Библиотека для работы с матрицами на языке C++. Библиотека была создана для работы с числами (int, float, double). В библиотеке представлены 2 класса: класс Matrix и класс SquareMatrix. Класс SquareMatrix 'является производным для класса Matrix. В этот класс был добавлен такой оператор, как детерминант и обратная матрица (матрица ^ -1).

Функции: 
friend Matrix trans (const Matrix & matrix);                    возвращает транспонированную матрицу
friend double det (const SquareMatrix & s_matrix);              возвращает детерминант матрицы
friend SquareMatrix inv (const SquareMatrix & s_matrix);        возвращает обратную матрицу (для квадратной матрицы)

Методы: Матричный минор (const int row, const int col) const;   возвращает матрицу без row-той строки и col-того столбца

Операторы: 
Dсе операторы над матрицами определены. Для полного просмотра операций вы можете использовать файл «Matrix.h».
