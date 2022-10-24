#include "../include/matrix.h"

#include <algorithm>

Matrix::Matrix() {
    _rows = 0;
    _cols = 0;
    _matrix = nullptr;
}

Matrix::Matrix(unsigned int rows, unsigned int cols) {
    _rows = rows;
    _cols = cols;
    _matrix = new Vector[rows];

    for (unsigned i = 0; i < _rows; ++i) {
        _matrix[i].setLen(_cols);
        _matrix[i].setVerticalState(false);
        _matrix[i].reallocateMemory();
    }
}

Matrix::Matrix(const Matrix &old) {
    *this = old;
}

Matrix::Matrix(std::initializer_list<Vector> list) {
    bool isCorrectList = true;
    bool isVertical = list.begin()->getVerticalState();
    unsigned size = list.begin()->getLen();

    if (std::any_of(list.begin(), list.end(),
                    [isVertical, size](auto i) {
                        return i.getVerticalState() != isVertical || i.getLen() != size;
                        })) {
        isCorrectList = false;
    }


    if (!isCorrectList) {
        _rows = 0;
        _cols = 0;
        _matrix = nullptr;
    } else {
        _rows = isVertical ? size : list.size();
        _cols = isVertical ? list.size() : size;
        _matrix = new Vector[_rows];

        unsigned counter = 0;
        for (const auto& i : list) {
            _matrix[counter] = i;
            _matrix[counter].setVerticalState(false);
            _matrix[counter].reallocateMemory();
            counter++;
        }
    }
}

Matrix::Matrix(unsigned int rows, unsigned int cols, std::initializer_list<double> list) {
    _rows = rows;
    _cols = cols;
    _matrix = new Vector[rows];

    for (unsigned i = 0, list_counter = 0; i < _rows; ++i) {
        _matrix[i].setLen(_cols);
        _matrix[i].setVerticalState(false);
        _matrix[i].reallocateMemory();

        for (unsigned j = 0; j < _cols; ++j) {
            _matrix[i][j] = *(list.begin() + list_counter);
            list_counter++;
        }
    }
}

unsigned Matrix::getRows() const {
    return _rows;
}

unsigned Matrix::getCols() const {
    return _cols;
}

void Matrix::setRows(unsigned rows) {
    _rows = rows;
}

void Matrix::setCols(unsigned cols) {
    _cols = cols;
}

Vector* Matrix::getRow(unsigned row) {
    auto *result = new Vector(_cols, false);

    for (unsigned i = 0; i < _cols; ++i) {
        (*result)[i] = _matrix[row][i];
    }

    return result;
}

Vector* Matrix::getCol(unsigned col) {
    auto *result = new Vector(_rows, true);

    for (unsigned i = 0; i < _rows; ++i) {
        (*result)[i] = _matrix[i][col];
    }

    return result;
}

Vector* Matrix::getDiag() {
    unsigned size = _rows > _cols ? _cols : _rows;
    auto *result = new Vector(size, true);

    for (unsigned i = 0; i < size; ++i) {
        (*result)[i] = _matrix[i][i];
    }

    return result;
}

Matrix* Matrix::getWithout(int row, int col) {
    auto *result = new Matrix(_rows - 1, _cols - 1);

    for (unsigned i = 0, row_counter = 0, col_counter; i < _rows; ++i) {
        col_counter = 0;

        for (unsigned j = 0; row != i && j < _cols; ++j) {
            if (j != col) {
                (*result)[row_counter][col_counter] = _matrix[i][j];
            }

            col_counter++;
        }

        row_counter++;
    }

    return result;
}

void Matrix::tr() {
    auto *tmp = new Matrix(_cols, _rows);

    for (unsigned i = 0; i < _cols; ++i) {
        for (unsigned j = 0; j < _rows; ++j) {
            (*tmp)[i][j] = _matrix[j][i];
        }
    }

    *this = *tmp;

    delete tmp;
}

double Matrix::det() {
    double result = 0;

    if (_rows == 2) {
        return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
    }

    for (unsigned i = 0; i < _cols; ++i) {
        auto *tmp = this->getWithout(0, i);

        result += (i % 2 == 0 ? 1 : -1) * _matrix[0][i] * tmp->det();

        delete tmp;
    }

    return result;
}

Matrix* Matrix::inv() {
    double deter = this->det();

    if (deter == 0) {
        return nullptr;
    }

    auto *result = new Matrix(_rows, _cols);

    for (unsigned i = 0; i < _rows; ++i) {
        for (unsigned j = 0; j < _cols; ++j) {
            auto *tmp = this->getWithout(i, j);

            (*result)[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * _matrix[i][j] * tmp->det();

            delete tmp;
        }
    }

    result->tr();

    return *result * (1. / deter);
}

Matrix* Matrix::operator+(const Matrix& a) const {
    if (_rows != a.getRows() || _cols != a.getCols()) {
        return nullptr;
    }

    auto *result = new Matrix(_rows, _cols);

    for (unsigned i = 0; i < _rows; ++i) {
        for (unsigned j = 0; j < _cols; ++j) {
            (*result)[i][j] = _matrix[i][j] + a[i][j];
        }
    }

    return result;
}

Matrix* Matrix::sumOn(int row, int col, double numb) const {
    auto *result = new Matrix(_rows, _cols);
    *result = *this;

    if (row != -1 && col != -1) {
        (*result)[row][col] += numb;
    } else if (row != -1) {
        for (unsigned i = 0; i < _cols; ++i) {
            (*result)[row][i] += numb;
        }
    } else if (col != -1) {
        for (unsigned i = 0; i < _rows; ++i) {
            (*result)[i][col] += numb;
        }
    }

    return result;
}

Matrix* Matrix::sumOn(int row, int col, const Vector &a) const {
    auto *result = new Matrix(_rows, _cols);
    *result = *this;

    for (unsigned i = 0; row != -1 && !a.getVerticalState() && i < _cols; ++i) {
        (*result)[row][i] += a[i];
    }

    for (unsigned i = 0; col != -1 && a.getVerticalState() && i < _rows; ++i) {
        (*result)[i][col] += a[i];
    }

    return result;
}

Matrix* Matrix::operator-(const Matrix& a) const {
    if (_rows != a.getRows() || _cols != a.getCols()) {
        return nullptr;
    }

    auto *result = new Matrix(_rows, _cols);

    for (unsigned i = 0; i < _rows; ++i) {
        for (unsigned j = 0; j < _cols; ++j) {
            (*result)[i][j] = _matrix[i][j] - a[i][j];
        }
    }

    return result;
}

Matrix* Matrix::subOn(int row, int col, double numb) const {
    auto *result = new Matrix(_rows, _cols);
    *result = *this;

    if (row != -1 && col != -1) {
        (*result)[row][col] -= numb;
    } else if (row != -1) {
        for (unsigned i = 0; i < _cols; ++i) {
            (*result)[row][i] -= numb;
        }
    } else if (col != -1) {
        for (unsigned i = 0; i < _rows; ++i) {
            (*result)[i][col] -= numb;
        }
    }

    return result;
}

Matrix* Matrix::subOn(int row, int col, const Vector &a) const {
    auto *result = new Matrix(_rows, _cols);
    *result = *this;

    for (unsigned i = 0; row != -1 && !a.getVerticalState() && i < _cols; ++i) {
        (*result)[row][i] -= a[i];
    }

    for (unsigned i = 0; col != -1 && a.getVerticalState() && i < _rows; ++i) {
        (*result)[i][col] -= a[i];
    }

    return result;
}

Matrix* Matrix::operator&(const Matrix& a) const {
    if (_rows != a.getRows() || _cols != a.getCols()) {
        return nullptr;
    }

    auto *result = new Matrix(_rows, _cols);

    for (unsigned i = 0; i < _rows; ++i) {
        for (unsigned j = 0; j < _cols; ++j) {
            (*result)[i][j] = _matrix[i][j] * a[i][j];
        }
    }

    return result;
}

Matrix* Matrix::operator*(const double &a) const {
    auto *result = new Matrix(_rows, _cols);

    for (unsigned i = 0; i < _rows; ++i) {
        for (unsigned j = 0; j < _cols; ++j) {
            (*result)[i][j] = _matrix[i][j] * a;
        }
    }

    return result;
}

Matrix* Matrix::operator*(const Vector &a) const {
    if ((a.getVerticalState() && _cols != a.getLen()) || (!a.getVerticalState() && _cols != 1)) {
        return nullptr;
    }

    auto *result = new Matrix(_rows, a.getVerticalState() ? 1 : a.getLen());

    if (a.getVerticalState()) {
        for (unsigned i = 0; i < _rows; ++i) {
            double sum = 0;

            for (unsigned j = 0; j < _cols; ++j) {
                sum += _matrix[i][j] * a[j];
            }

            (*result)[i][0] = sum;
        }
    } else {
        for (unsigned i = 0; i < _rows; ++i) {
            for (unsigned j = 0; j < a.getLen(); ++j) {
                (*result)[i][j] = _matrix[i][0] * a[j];
            }
        }
    }

    return result;
}

Matrix* Matrix::operator*(const Matrix &a) const {
    if (_cols != a.getRows()) {
        return nullptr;
    }

    auto *result = new Matrix(_rows, a.getCols());

    double sum;

    for (unsigned i = 0; i < _rows; ++i) {
        for (unsigned j = 0; i < a.getCols(); ++j) {
            sum = 0;

            for (unsigned k = 0; k < _cols; ++k) {
                sum += _matrix[i][k] * a[k][j];
            }

            (*result)[i][j] = sum;
        }
    }

    return result;
}

Vector& Matrix::operator[](unsigned index) const {
    return _matrix[index];
}

Matrix& Matrix::operator=(const Matrix &a) {
    if (&a != this) {
        delete[] _matrix;

        _rows = a.getRows();
        _cols = a.getCols();
        _matrix = new Vector[a.getRows()];

        for (unsigned i = 0; i < _rows; ++i) {
            _matrix[i].setLen(_cols);
            _matrix[i].setVerticalState(false);
            _matrix[i] = a[i];
        }
    }

    return *this;
}

std::ostream& operator<<(std::ostream &out, const Matrix &item) {
    for (unsigned i = 0; i < item._rows; ++i) {
        for (unsigned j = 0; j < item._cols; ++j) {
            out << item[i][j];

            if (j != item._cols - 1) {
                out << ' ';
            }
        }

        out << '\n';
    }

    return out;
}

Matrix::~Matrix() {
    delete[] _matrix;
}
