#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_

#include "vector.h"

class Matrix {
 private:
    Vector *_matrix;
    size_t _rows;
    size_t _cols;

 public:
    Matrix() : _matrix(nullptr), _rows(0), _cols(0) { }
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix &old);
    explicit Matrix(std::initializer_list<Vector> list);
    Matrix(size_t rows, size_t cols, std::initializer_list<double> list);

    size_t getRows() const;
    size_t getCols() const;

    Vector getRow(size_t row) const;
    Vector getCol(size_t col) const;
    Vector getDiag() const;
    Matrix getWithout(size_t row, size_t col) const;

    Matrix tr();
    double det() const;
    Matrix inv() const;

    Matrix operator+(const Matrix& operand) const;
    Matrix sumOn(size_t row, size_t col, double numb) const;
    Matrix sumOn(size_t row, size_t col, const Vector& operand) const;
    Matrix operator-(const Matrix& operand) const;
    Matrix subOn(int row, int col, double numb) const;
    Matrix subOn(int row, int col, const Vector& operand) const;
    Matrix operator&(const Matrix& operand) const;
    Matrix operator*(const double& operand) const;
    Matrix operator*(const Vector& operand) const;
    Matrix operator*(const Matrix& operand) const;

    Vector& operator[](size_t index) const;

    Matrix& operator=(const Matrix& operand);
    Matrix& operator+=(const Matrix& operand);
    Matrix& operator-=(const Matrix& operand);
    Matrix& operator*=(const Matrix& operand);
    Matrix& operator&=(const Matrix& operand);

    friend std::ostream& operator<<(std::ostream &out, const Matrix &item);

    ~Matrix();
};

#endif  // INCLUDE_MATRIX_H_
