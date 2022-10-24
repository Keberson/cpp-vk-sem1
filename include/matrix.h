#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_

#include "vector.h"

class Matrix {
 private:
    Vector *_matrix;
    unsigned _rows;
    unsigned _cols;

 public:
    Matrix();
    Matrix(unsigned rows, unsigned cols);
    Matrix(const Matrix &old);
    explicit Matrix(std::initializer_list<Vector> list);
    Matrix(unsigned rows, unsigned cols, std::initializer_list<double> list);

    unsigned getRows() const;
    unsigned getCols() const;

    void setRows(unsigned rows);
    void setCols(unsigned cols);

    Vector* getRow(unsigned row);
    Vector* getCol(unsigned col);
    Vector* getDiag();
    Matrix* getWithout(int row, int col);

    void tr();
    double det();
    Matrix* inv();

    Matrix* operator+(const Matrix& a) const;
    Matrix* sumOn(int row, int col, double numb) const;
    Matrix* sumOn(int row, int col, const Vector &a) const;
    Matrix* operator-(const Matrix& a) const;
    Matrix* subOn(int row, int col, double numb) const;
    Matrix* subOn(int row, int col, const Vector &a) const;
    Matrix* operator&(const Matrix& a) const;
    Matrix* operator*(const double &a) const;
    Matrix* operator*(const Vector &a) const;
    Matrix* operator*(const Matrix &a) const;

    Vector& operator[](unsigned index) const;

    Matrix& operator=(const Matrix &a);

    friend std::ostream& operator<<(std::ostream &out, const Matrix &item);

    ~Matrix();
};

#endif  // INCLUDE_MATRIX_H_
