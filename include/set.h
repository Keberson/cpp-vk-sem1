#ifndef INCLUDE_SET_H_
#define INCLUDE_SET_H_

#include <list>

#include "iterator.h"

template<typename T>
class Set {
private:
    std::list<T> _arr;

    void push(T elem);
    T pop();
    void siftUp(size_t index);
    void siftDown(size_t index);
public:
    typedef BiIterator<T> iterator;

    Set() = default;
    Set(std::initializer_list<T> list);
    Set(BiIterator<T> begin, BiIterator<T> end);
    Set(Set &another);

    Set<T>& operator=(const Set &another);
    T& operator[](size_t index);

    iterator begin() const;
    iterator end() const;

    void insert(T elem);
    void erase(T elem);

    size_t size() const;
    bool empty() const;

    iterator find(const T &key) const;
    iterator lower_bound(const T &key) const;

    ~Set() = default;
};

#endif  // INCLUDE_SET_H_
