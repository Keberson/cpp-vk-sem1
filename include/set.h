#ifndef INCLUDE_SET_H_
#define INCLUDE_SET_H_

#include <iterator>
#include <list>

template<typename T>
bool comparator(T &a, T &b);

template<class T>
class Set {
private:
    std::list<T> _arr;

    void push(T elem);
    T pop();
    void siftUp(size_t index);
    void siftDown(size_t index);
public:
    Set() = default;
    Set(typename T::iterator begin, typename T::iterator end);
    Set(std::initializer_list<T> list);
    Set(Set &another);

    Set<T>& operator=(const Set &another);
    T& operator[](const size_t index);

    typename T::iterator begin();
    typename T::iterator end();

    void insert(T &elem);
    void erase(T &elem);

    size_t size() const;
    bool empty() const;

    typename T::iterator find(const T &key);
    typename T::iterator lower_bound(const T &key);

    ~Set() = default;
};

#endif  // INCLUDE_SET_H_
