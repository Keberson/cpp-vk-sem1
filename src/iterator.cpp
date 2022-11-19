#include "../include/iterator.h"

template<typename T>
bool BiIterator<T>::operator!=(BiIterator<T> const& other) const {
    return _p != other._p;
}

template<typename T>
bool BiIterator<T>::operator==(BiIterator<T> const& other) const {
    return _p == other._p;
}

template<typename T>
typename BiIterator<T>::reference BiIterator<T>::operator*() const {
    return *_p;
}

template<typename T>
BiIterator<T> &BiIterator<T>::operator++() {
    ++_p;
    return *this;
}

template<typename T>
BiIterator<T> &BiIterator<T>::operator--() {
    --_p;
    return *this;
}

template<typename T>
T *BiIterator<T>::operator->() {
    return _p;
}

template<typename T>
const BiIterator<T> BiIterator<T>::operator++(int) {
    BiIterator<T> temp{*this};

    ++(*this);

    return temp;
}

template<typename T>
const BiIterator<T> BiIterator<T>::operator--(int) {
    BiIterator<T> temp{*this};

    --(*this);

    return temp;
}

