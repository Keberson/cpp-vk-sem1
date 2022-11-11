#include "../include/matrix.h"

#include <algorithm>

Matrix::Matrix(size_t rows, size_t cols) {
    _rows = rows;
    _cols = cols;
    _matrix = new Vector[rows];

    for (size_t i = 0; i < _rows; ++i) {
        _matrix[i].setLen(_cols);
        _matrix[i].setVerticalState(false);
        _matrix[i].reallocateMemory();
    }
}

Matrix::Matrix(const Matrix &old) : Matrix() {
    *this = old;
}

Matrix::Matrix(std::initializer_list<Vector> list) {
    bool isCorrectList = true;
    size_t size = list.begin()->getLen();

    if (std::any_of(list.begin(), list.end(),
                    [size](auto i) {
                        return i.getLen() != size;
                        })) {
        isCorrectList = false;
    }


    if (!isCorrectList) {
        throw std::invalid_argument("Matrix: Invalid initializer list");
    } else {
        _rows = list.size();
        _cols = size;
        _matrix = new Vector[_rows];

        size_t counter = 0;
        for (const auto& i : list) {
            _matrix[counter] = i;
            _matrix[counter].setVerticalState(false);
            counter++;
        }
    }
}

Matrix::Matrix(size_t rows, size_t cols, std::initializer_list<double> list) {
    _rows = rows;
    _cols = cols;
    _matrix = new Vector[rows];

    for (size_t i = 0, list_counter = 0; i < _rows; ++i) {
        _matrix[i].setLen(_cols);
        _matrix[i].setVerticalState(false);
        _matrix[i].reallocateMemory();

        for (size_t j = 0; j < _cols; ++j) {
            _matrix[i][j] = *(list.begin() + list_counter);
            list_counter++;
        }
    }
}

size_t Matrix::getRows() const {
    return _rows;
}

size_t Matrix::getCols() const {
    return _cols;
}

Vector Matrix::getRow(size_t row) const {
    if (row > _rows) {
        throw std::invalid_argument("getRow: Invalid argument");
    }

    Vector result(_cols, false);

    for (size_t i = 0; i < _cols; ++i) {
        result[i] = _matrix[row][i];
    }

    return result;
}

Vector Matrix::getCol(size_t col) const {
    if (col > _cols) {
        throw std::invalid_argument("getRow: Invalid argument");
    }

    Vector result(_rows, true);

    for (size_t i = 0; i < _rows; ++i) {
        result[i] = _matrix[i][col];
    }

    return result;
}

Vector Matrix::getDiag() const {
    size_t size = _rows > _cols ? _cols : _rows;
    Vector result(_rows, true);

    for (size_t i = 0; i < size; ++i) {
        result[i] = _matrix[i][i];
    }

    return result;
}

Matrix Matrix::getWithout(size_t row, size_t col) const {
    Matrix result(_rows - 1, _cols - 1);

    for (size_t i = 0, row_counter = 0, col_counter; i < _rows; ++i) {
        col_counter = 0;

        if (row == i) {
            continue;
        }

        for (size_t j = 0; j < _cols; ++j) {
            if (j != col) {
                result[row_counter][col_counter] = _matrix[i][j];
                col_counter++;
            }
        }

        row_counter++;
    }

    return result;
}

Matrix Matrix::tr() {
    Matrix tmp(_cols, _rows);

    for (size_t i = 0; i < _cols; ++i) {
        for (size_t j = 0; j < _rows; ++j) {
            tmp[i][j] = _matrix[j][i];
        }
    }

    return tmp;
}

double Matrix::det() const {
    double result = 0;

    if (_rows != _cols) {
        throw std::invalid_argument("det: Invalid matrix");
    }

    if (_rows == 1) {
        return _matrix[0][0];
    }

    if (_rows == 2) {
        return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
    }

    for (size_t i = 0; i < _cols; ++i) {
        auto tmp = this->getWithout(0, i);

        result += (i % 2 == 0 ? 1 : -1) * _matrix[0][i] * tmp.det();
    }

    return result;
}

Matrix Matrix::inv() const {
    double deter = this->det();

    if (deter == 0) {
        throw std::invalid_argument("inv: Determinant is null");
    }

    Matrix raw(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            auto tmp = this->getWithout(i, j);

            raw[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * tmp.det();
        }
    }

    return raw.tr() * (1. / deter);
}

Matrix Matrix::operator+(const Matrix& operand) const {
    if (_rows != operand.getRows() || _cols != operand.getCols()) {
        throw std::invalid_argument("sum: Invalid matrices");
    }

    Matrix result(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            result[i][j] = _matrix[i][j] + operand[i][j];
        }
    }

    return result;
}

Matrix Matrix::sumOn(size_t row, size_t col, double numb) const {
    Matrix result(*this);

    if (row != -1 && col != -1) {
        result[row][col] += numb;
    } else if (row != -1) {
        for (size_t i = 0; i < _cols; ++i) {
            result[row][i] += numb;
        }
    } else if (col != -1) {
        for (size_t i = 0; i < _rows; ++i) {
            result[i][col] += numb;
        }
    }

    return result;
}

Matrix Matrix::sumOn(size_t row, size_t col, const Vector& operand) const {
    Matrix result(*this);

    if (row != -1 && !operand.getVerticalState()) {
        for (size_t i = 0; i < _cols; ++i) {
            result[row][i] += operand[i];
        }
    }

    if (col != -1 && operand.getVerticalState()) {
        for (size_t i = 0;  i < _rows; ++i) {
            result[i][col] += operand[i];
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix& operand) const {
    if (_rows != operand.getRows() || _cols != operand.getCols()) {
        throw std::invalid_argument("Invalid matrices");
    }

    Matrix result(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            result[i][j] = _matrix[i][j] - operand[i][j];
        }
    }

    return result;
}

Matrix Matrix::subOn(int row, int col, double numb) const {
    if ((row < 0 && row != -1) || row >= (int)_rows) {
        throw std::invalid_argument("subOn: Invalid row");
    }

    if ((col < 0 && col != -1) || col >= (int)_cols) {
        throw std::invalid_argument("subOn: Invalid col");
    }

    Matrix result(*this);

    if (row != -1 && col != -1) {
        result[row][col] -= numb;
    } else if (row != -1) {
        for (size_t i = 0; i < _cols; ++i) {
            result[row][i] -= numb;
        }
    } else if (col != -1) {
        for (size_t i = 0; i < _rows; ++i) {
            result[i][col] -= numb;
        }
    }

    return result;
}

Matrix Matrix::subOn(int row, int col, const Vector& operand) const {
    if ((row < 0 && row != -1) || row >= (int)_rows) {
        throw std::invalid_argument("subOn: Invalid row");
    }

    if ((col < 0 && col != -1) || col >= (int)_cols) {
        throw std::invalid_argument("subOn: Invalid col");
    }

    Matrix result(*this);

    if (row != -1 && !operand.getVerticalState()) {
        for (size_t i = 0; i < _cols; ++i) {
            result[row][i] -= operand[i];
        }
    }

    if (col != -1 && operand.getVerticalState()) {
        for (size_t i = 0; i < _rows; ++i) {
            result[i][col] -= operand[i];
        }
    }

    return result;
}

Matrix Matrix::operator&(const Matrix& operand) const {
    if (_rows != operand.getRows() || _cols != operand.getCols()) {
        throw std::invalid_argument("Invalid matrices");
    }

    Matrix result(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            result[i][j] = _matrix[i][j] * operand[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator*(const double& operand) const {
    Matrix result(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            result[i][j] = _matrix[i][j] * operand;
        }
    }

    return result;
}

Matrix Matrix::operator*(const Vector& operand) const {
    if ((operand.getVerticalState() && _cols != operand.getLen()) ||
            (!operand.getVerticalState() && _cols != 1)) {
        throw std::invalid_argument("Invalid matrix and vector");
    }

    Matrix result(_rows, operand.getVerticalState() ? 1 : operand.getLen());

    if (operand.getVerticalState()) {
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                result[i][0] += _matrix[i][j] * operand[j];
            }
        }
    } else {
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < operand.getLen(); ++j) {
                result[i][j] = _matrix[i][0] * operand[j];
            }
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix& operand) const {
    if (_cols != operand.getRows()) {
        throw std::invalid_argument("Invalid matrices");
    }

    Matrix result(_rows, operand.getCols());

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < operand.getCols(); ++j) {
            for (size_t k = 0; k < _cols; ++k) {
                result[i][j] += _matrix[i][k] * operand[k][j];
            }
        }
    }

    return result;
}

Vector& Matrix::operator[](size_t index) const {
    return _matrix[index];
}

Matrix& Matrix::operator=(const Matrix& operand) {
    if (&operand != this) {
        delete[] _matrix;

        _rows = operand.getRows();
        _cols = operand.getCols();
        _matrix = new Vector[operand.getRows()];

        for (size_t i = 0; i < _rows; ++i) {
            _matrix[i].setLen(_cols);
            _matrix[i].setVerticalState(false);
            _matrix[i] = operand[i];
        }
    }

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& operand) {
    return *this = *this + operand;
}

Matrix& Matrix::operator-=(const Matrix& operand) {
    return *this = *this - operand;
}

Matrix& Matrix::operator*=(const Matrix& operand) {
    return *this = *this * operand;
}

Matrix& Matrix::operator&=(const Matrix& operand) {
    return *this = *this & operand;
}

std::ostream& operator<<(std::ostream &out, const Matrix &item) {
    for (size_t i = 0; i < item._rows; ++i) {
        for (size_t j = 0; j < item._cols; ++j) {
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
