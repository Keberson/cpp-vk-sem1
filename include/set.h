#ifndef INCLUDE_SET_H_
#define INCLUDE_SET_H_

#include <list>

#include "iterator.h"

template<typename T>
class Set {
 private:
    Node<T> *_begin;
    Node<T> *_end;
    size_t _size;

    void push(T elem);

 public:
    typedef Node<T> node;
    typedef BiIterator<T> iterator;

    Set(): _begin(nullptr), _end(nullptr), _size(0) {}
    explicit Set(std::initializer_list<T> list);
    Set(T *begin, T *end);
    Set(const Set &another);

    Set<T>& operator=(const Set<T> &another);
    node& operator[](size_t index) const;

    iterator begin() const;
    iterator end() const;

    void insert(T elem);
    void erase(T elem);

    size_t size() const;
    bool empty() const;

    iterator find(const T &key) const;
    iterator lower_bound(const T &key) const;

    ~Set();
};

template<typename T>
void Set<T>::push(T elem) {
    node *tmp = new node;

    tmp->_val = elem;
    tmp->_next = nullptr;
    tmp->_prev = nullptr;

    _size++;

    if (_size - 1 == 0) {
        _begin = _end = tmp;
    } else if (_size - 1 == 1) {
        if (tmp->_val > _begin->_val) {
            _end = tmp;
        } else {
            _end = _begin;
            _begin = tmp;
        }

        _begin->_next = _end;
        _end->_prev = _begin;
    } else if (*find(elem) != elem) {
        auto current = lower_bound(elem).getNode();

        if (current->_next == nullptr) {
            if (current->_val > tmp->_val) {
                tmp->_prev = current->_prev;
                tmp->_next = _end;
                current->_prev->_next = tmp;
                current->_prev = tmp;
            } else {
                current->_next = tmp;
                _end = tmp;
                _end->_prev = current;
            }
        } else {
            tmp->_next = current;
            tmp->_prev = current->_prev;

            if (current->_prev != nullptr) {
                current->_prev->_next = tmp;
            } else {
                _begin = tmp;
                _begin->_next = current;
            }

            current->_prev = tmp;
        }
    } else {
        _size--;

        delete tmp;
    }
}

template<typename T>
Set<T>::Set(T *begin, T *end) : Set<T>() {
    while (begin != end) {
        if (size() == 0 || *find(*begin) != *begin) {
            push(*begin);
        }

        begin++;
    }
}

template<typename T>
Set<T>::Set(std::initializer_list<T> list) : Set<T>() {
    for (const auto &i : list) {
        push(i);
    }
}

template<typename T>
Set<T>::Set(const Set<T> &another) : Set<T>() {
    *this = another;
}

template<typename T>
Set<T>& Set<T>::operator=(const Set &another) {
    while (!empty()) {
        Node<T> *tmp = _end;

        _end = _end->_prev;
        _size--;

        delete tmp;
    }

    _begin = nullptr;
    _end = nullptr;

    for (size_t i = 0; i < another.size(); ++i) {
        push((another[i])._val);
    }

    _size = another.size();

    return *this;
}

template<typename T>
typename Set<T>::node& Set<T>::operator[](size_t index) const {
    if (index > size()) {
        throw std::invalid_argument("Set: Invalid index");
    }

    size_t counter = 0;
    node *res = _begin;

    while (counter != index) {
        res = res->_next;
        counter++;
    }

    return *res;
}

template<typename T>
typename Set<T>::iterator Set<T>::begin() const {
    return iterator(_begin);
}

template<typename T>
typename Set<T>::iterator Set<T>::end() const {
    return iterator(_end);
}

template<typename T>
void Set<T>::insert(T elem) {
    if (size() == 0 || *find(elem) != elem) {
        push(elem);
    }
}

template<typename T>
void Set<T>::erase(T elem) {
    if (size() != 0) {
        auto founded = find(elem);

        if ((*founded) == elem) {
            auto current = founded.getNode();

            if (current->_prev != nullptr) {
                current->_prev->_next = current->_next;
            }

            if (current->_next != nullptr) {
                current->_next->_prev = current->_prev;
            }

            delete current;

            _size--;

            if (_size == 1) {
                _end = _begin;
            } else if (_size == 0) {
                _begin = _end = nullptr;
            }
        }
    }
}

template<typename T>
size_t Set<T>::size() const {
    return _size;
}

template<typename T>
bool Set<T>::empty() const {
    return _size == 0;
}

template<typename T>
typename Set<T>::iterator Set<T>::find(const T &key) const {
    if (key <= _begin->_val || key >= _end->_val) {
        return end();
    }

    size_t l = 0;
    size_t r = size() - 2;
    iterator res;

    while (r - l > 1) {
        size_t mid = (r + l) / 2;

        if ((*this)[mid]._val < key) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    if ((*this)[l]._val == key) {
        res = iterator((*this)[l]);
    } else if ((*this)[r]._val == key) {
        res = iterator((*this)[r]);
    } else {
        res = end();
    }

    return res;
}

template<typename T>
typename Set<T>::iterator Set<T>::lower_bound(const T &key) const {
    if (key <= _begin->_val) {
        return begin();
    }

    if (key >= _end->_val) {
        return end();
    }

    size_t l = 0;
    size_t r = size() - 1;
    size_t mid;

    while (r >= l) {
        mid = (l + r) / 2;

        if (key < (*this)[mid]._val) {
            r = mid - 1;
        } else if (key > (*this)[mid]._val) {
            l = mid + 1;
        } else {
            return iterator((*this)[mid]);
        }
    }

    return iterator((*this)[mid + ((*this)[mid]._val >= key ? 0 : + 1)]);
}

template<typename T>
Set<T>::~Set() {
    while (_begin != nullptr && _begin->_next != nullptr) {
        Node<T> *tmp = _begin;

        _begin = _begin->_next;

        delete tmp;
    }

    delete _begin;
}

#endif  // INCLUDE_SET_H_
