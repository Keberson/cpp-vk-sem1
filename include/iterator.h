#ifndef INCLUDE_ITERATOR_H_
#define INCLUDE_ITERATOR_H_

#include <iterator>

template<typename T>
class BiIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
private:
    T *_p;
public:
    BiIterator() : _p(nullptr) {}
    explicit BiIterator(T *p) : _p(p) {}
    BiIterator(const BiIterator<T> &it) : _p(it._p) {}

    bool operator!=(BiIterator<T> const &other) const;
    bool operator==(BiIterator<T> const &other) const;
    typename BiIterator<T>::reference operator*() const;
    BiIterator<T> &operator++();
    BiIterator<T> &operator--();
    const BiIterator<T> operator++(int);
    const BiIterator<T> operator--(int);
    T *operator->();
};

#endif  // INCLUDE_ITERATOR_H_
