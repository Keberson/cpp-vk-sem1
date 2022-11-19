#include "../include/set.h"

template<typename T>
bool comparator(T &a, T &b) {
    return a > b;
}

template<typename T>
void Set<T>::siftUp(size_t index) {
    while (index != 0 && _cmp(_arr[index], _arr[(index - 1) / 2])) {
        std::swap(_arr[index], _arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

template<class T>
void Set<T>::siftDown(size_t index) {
    while (2 * index + 1 < _arr.size()) {
        auto left = 2 * index + 1;
        auto right = 2 * index + 2;
        auto j = left;

        if (right < _arr.size() && _cmp(_arr[right], _arr[left])) {
            j = right;
        }

        if (_cmp(_arr[index], _arr[j])) {
            break;
        }

        std::swap(_arr[index], _arr[j]);
        index = j;
    }
}

template<class T>
void Set<T>::push(T elem) {
    if (find(elem) != _arr.end()) {
        _arr.push(elem);
        siftUp(_arr.size() - 1);
    }
}

template<class T>
T Set<T>::pop() {
    T min = _arr[0];

    _arr[0] = _arr[_arr.size() - 1];
    siftDown(0);

    return min;
}

template<class T>
Set<T>::Set(typename T::iterator begin, typename T::iterator end) : Set<T>() {
    while (begin != end) {
        _arr.push(*begin);
        begin++;
    }
}

template<class T>
Set<T>::Set(std::initializer_list<T> list) : Set<T>() {
    for (const auto &i : list) {
        push(i);
    }
}

template<class T>
Set<T>::Set(Set &another) : Set<T>() {
    *this = another;
}

template<class T>
Set<T>& Set<T>::operator=(const Set &another) {
    while (!_arr.empty()) {
        pop();
    }

    for (size_t i = 0; i < another.size(); ++i) {
        _arr.push(another[i]);
    }

    return *this;
}

template<class T>
T& Set<T>::operator[](const size_t index) {
    if (index > _arr.size()) {
        throw std::invalid_argument("Set: Invalid index");
    }

    return _arr[index];
}

template<class T>
typename T::iterator Set<T>::begin() {
    return _arr.begin();
}

template<class T>
typename T::iterator Set<T>::end() {
    return _arr.end();
}

template<class T>
void Set<T>::insert(T &elem) {
    if (find(elem) != _arr.end()) {
        _arr.insert(lower_bound(elem), elem);
    }
}

template<class T>
void Set<T>::erase(T &elem) {
    auto founded = find(elem);

    if (founded != _arr.end()) {
        _arr.erase(founded);
    }
}

template<class T>
size_t Set<T>::size() const {
    return _arr.size();
}

template<class T>
bool Set<T>::empty() const {
    return _arr.empty();
}

template<class T>
typename T::iterator Set<T>::find(const T &key) {
    if (key <= _arr[0] || key >= *_arr.end()) {
        return _arr.end();
    }

    size_t index = 1;

    while (index < _arr.size() && _arr[index] < key) {
        index *= 2;
    }

    size_t low = index / 2;
    size_t high = index >= _arr.size() ? _arr.size() - 1 : index;
    size_t middle = 0;
    bool isFound = false;

    while (high > low && !isFound) {
         middle = (low + high) / 2;

         if (_arr[middle] == key) {
             isFound = true;
         }

        if (_arr[middle] > key) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
     }

     return isFound ? _arr.begin() + middle : _arr.end();
}

template<class T>
typename T::iterator Set<T>::lower_bound(const T &key) {
    if (key <= _arr[0]) {
        return 0;
    }

    size_t index = 1;

    while (index < _arr.size() && _arr[index] < key) {
        index *= 2;
    }

    size_t low = index / 2;
    size_t high = index >= _arr.size() ? _arr.size() - 1 : index;
    size_t middle = 0;

    while (high >= low) {
        middle = (low + high) / 2;

        if (key < _arr[middle]) {
            high = middle - 1;
        } else if (key > _arr[middle]) {
            low = middle + 1;
        } else {
            return middle;
        }
    }

    return _arr.begin() + middle + _arr[middle] >= key ? 0 : 1;
}
