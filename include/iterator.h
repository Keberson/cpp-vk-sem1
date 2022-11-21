#ifndef INCLUDE_ITERATOR_H_
#define INCLUDE_ITERATOR_H_

#include <iterator>

#include "node.h"

template<typename T>
class BiIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
 private:
    Node<T> *_p;
 public:
    BiIterator() : _p(nullptr) {}
    explicit BiIterator(Node<T> *p) : _p(p) {}
    explicit BiIterator(Node<T> &p) : _p(&p) {}
    BiIterator(const BiIterator<T> &it) : _p(it._p) {}

    bool operator!=(BiIterator<T> const& other) const;
    bool operator==(BiIterator<T> const& other) const;

    T& operator*() const;

    BiIterator<T>& operator++();
    BiIterator<T>& operator--();
    const BiIterator<T> operator++(int);
    const BiIterator<T> operator--(int);

    T* operator->();
};

template<typename T>
bool BiIterator<T>::operator!=(BiIterator<T> const& other) const {
    return _p != other._p;
}

template<typename T>
bool BiIterator<T>::operator==(BiIterator<T> const& other) const {
    return _p == other._p;
}

template<typename T>
T& BiIterator<T>::operator*() const {
    return _p->_val;
}

template<typename T>
BiIterator<T>& BiIterator<T>::operator++() {
    if (_p != nullptr && _p->_next != nullptr) {
        _p = _p->_next;
    }

    return *this;
}

template<typename T>
BiIterator<T>& BiIterator<T>::operator--() {
    if (_p != nullptr && _p->_prev != nullptr) {
        _p = _p->_prev;
    }

    return *this;
}

template<typename T>
T* BiIterator<T>::operator->() {
    return &(_p->_val);
}

template<typename T>
const BiIterator<T> BiIterator<T>::operator++(int) {
    BiIterator<T> temp(*this);

    ++(*this);

    return temp;
}

template<typename T>
const BiIterator<T> BiIterator<T>::operator--(int) {
    BiIterator<T> temp{*this};

    --(*this);

    return temp;
}

#endif  // INCLUDE_ITERATOR_H_
