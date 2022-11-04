#include "../include/vector.h"

Vector::Vector(const Vector &old) {
    _vector = nullptr;
    *this = old;
}

Vector::Vector(std::initializer_list<double> list, bool isVertical) : Vector(list.size(), isVertical) {
    size_t counter = 0;

    for (auto i : list) {
        _vector[counter] = i;
        counter++;
    }
}

void Vector::reallocateMemory() {
    delete[] _vector;

    if (_len > 0) {
        _vector = new double[_len];
    } else {
        _vector = nullptr;
    }
}

size_t Vector::getLen() const {
    return _len;
}

bool Vector::getVerticalState() const {
    return _isVertical;
}

void Vector::setLen(size_t len) {
    if (len < 1) {
        throw std::invalid_argument("Vector's len can't be < 1");
    }

    _len = len;
}

void Vector::setVerticalState(bool isVertical) {
    _isVertical = isVertical;
}

Vector Vector::operator+(const Vector& operand) const {
    if (_len != operand.getLen() || _isVertical != operand.getVerticalState()) {
        throw std::invalid_argument("Invalid vectors");
    }

    Vector result(_len, _isVertical);

    for (size_t i = 0; i < _len; ++i) {
        result[i] = _vector[i] + operand[i];
    }

    return result;
}

Vector Vector::sumOn(size_t index, double numb) const {
    if (index > _len || index < 0) {
        throw std::invalid_argument("Invalid index");
    }

    Vector result(_len, _isVertical);

    result = *this;

    result[index] = _vector[index] + numb;

    return result;
}

Vector Vector::operator-(const Vector& operand) const {
    if (_len != operand.getLen() || _isVertical != operand.getVerticalState()) {
        throw std::invalid_argument("Invalid vectors");
    }

    Vector result(_len, _isVertical);

    for (size_t i = 0; i < _len; ++i) {
        result[i] = _vector[i] - operand[i];
    }

    return result;
}

Vector Vector::subOn(size_t index, double numb) const {
    if (index > _len || index < 0) {
        throw std::invalid_argument("Invalid index");
    }

    Vector result(_len, _isVertical);

    result = *this;

    result[index] = _vector[index] - numb;

    return result;
}

Vector Vector::operator&(const Vector& operand) const {
    if (_len != operand.getLen() || _isVertical != operand.getVerticalState()) {
        throw std::invalid_argument("Invalid vectors");
    }

    Vector result(_len, _isVertical);

    for (size_t i = 0; i < _len; ++i) {
        result[i] = _vector[i] * operand[i];
    }

    return result;
}

Vector Vector::operator*(const double& operand) const {
    Vector result(_len, _isVertical);

    for (size_t i = 0; i < _len; ++i) {
        result[i] = _vector[i] * operand;
    }

    return result;
}

double &Vector::operator[](size_t index) const {
    return _vector[index];
}

Vector &Vector::operator=(const Vector& operand) {
    if (&operand != this) {
        if (_len != 0) {
            delete[] _vector;
        }

        _len = operand.getLen();
        _isVertical = operand.getVerticalState();
        _vector = new double[_len];

        for (size_t i = 0; i < _len; ++i) {
            _vector[i] = operand[i];
        }
    }

    return *this;
}

Vector& Vector::operator+=(const Vector& operand) {
    return *this = *this + operand;
}

Vector& Vector::operator-=(const Vector& operand) {
    return *this = *this - operand;
}

Vector& Vector::operator&=(const Vector& operand) {
    return *this = *this & operand;
}

std::ostream &operator<<(std::ostream &out, const Vector &item) {
    for (size_t i = 0; i < item._len; ++i) {
        out << item[i];

        if (i != item._len - 1) {
            out << (item._isVertical ? '\n' : ' ');
        }
    }

    return out;
}

Vector::~Vector() {
    if (_len != 0) {
        delete[] _vector;
    }
}
