#include "../include/vector.h"

Vector::Vector() {
    _vector = nullptr;
    _len = 0;
    _isVertical = false;
}

Vector::Vector(unsigned int len, bool isVertical) {
    _len = len;
    _isVertical = isVertical;
    _vector = new double[len];
}

Vector::Vector(const Vector &old) {
    _vector = nullptr;
    *this = old;
}

Vector::Vector(std::initializer_list<double> list, bool isVertical) : Vector(list.size(), isVertical) {
    unsigned counter = 0;

    for (auto i : list) {
        _vector[counter] = i;
        counter++;
    }
}

void Vector::reallocateMemory() {
    delete[] _vector;

    _vector = new double[_len];
}

unsigned Vector::getLen() const {
    return _len;
}

bool Vector::getVerticalState() const {
    return _isVertical;
}

void Vector::setLen(unsigned int len) {
    _len = len;
}

void Vector::setVerticalState(bool isVertical) {
    _isVertical = isVertical;
}

Vector *Vector::operator+(const Vector &a) const {
    if (_len != a.getLen() || _isVertical != a.getVerticalState()) {
        return nullptr;
    }

    auto *result = new Vector(_len, _isVertical);

    for (unsigned i = 0; i < _len; ++i) {
        (*result)[i] = _vector[i] + a[i];
    }

    return result;
}

Vector *Vector::sumOn(int index, double numb) const {
    if (index > _len || index < 0) {
        return nullptr;
    }

    auto *result = new Vector(_len, _isVertical);

    *result = *this;

    (*result)[index] = _vector[index] + numb;

    return result;
}

Vector *Vector::operator-(const Vector &a) const {
    if (_len != a.getLen() || _isVertical != a.getVerticalState()) {
        return nullptr;
    }

    auto *result = new Vector(_len, _isVertical);

    for (unsigned i = 0; i < _len; ++i) {
        (*result)[i] = _vector[i] - a[i];
    }

    return result;
}

Vector *Vector::subOn(int index, double numb) const {
    if (index > _len || index < 0) {
        return nullptr;
    }

    auto *result = new Vector(_len, _isVertical);

    *result = *this;

    (*result)[index] = _vector[index] - numb;

    return result;
}

Vector *Vector::operator&(const Vector &a) const {
    if (_len != a.getLen() || _isVertical != a.getVerticalState()) {
        return nullptr;
    }

    auto *result = new Vector(_len, _isVertical);

    for (unsigned i = 0; i < _len; ++i) {
        (*result)[i] = _vector[i] * a[i];
    }

    return result;
}

Vector *Vector::operator*(const double &a) const {
    auto *result = new Vector(_len, _isVertical);

    for (unsigned i = 0; i < _len; ++i) {
        (*result)[i] = _vector[i] * a;
    }

    return result;
}

double &Vector::operator[](unsigned int index) const {
    return _vector[index];
}

Vector &Vector::operator=(const Vector &a) {
    if (&a != this) {
        if (_len != 0)
            delete[] _vector;

        _len = a.getLen();
        _isVertical = a.getVerticalState();
        _vector = new double[_len];

        for (unsigned i = 0; i < _len; ++i) {
            _vector[i] = a[i];
        }
    }

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Vector &item) {
    for (unsigned i = 0; i < item._len; ++i) {
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
