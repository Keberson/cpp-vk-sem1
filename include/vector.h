#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <iostream>

class Vector {
 private:
    double *_vector;
    unsigned _len;
    bool _isVertical;

 public:
    Vector();
    explicit Vector(unsigned len, bool isVertical);
    Vector(std::initializer_list<double> list, bool isVertical);

    void reallocateMemory();
    unsigned getLen() const;
    bool getVerticalState() const;
    void setLen(unsigned len);
    void setVerticalState(bool isVertical);

    Vector* operator+(const Vector& a) const;
    Vector* sumOn(int index, double numb) const;
    Vector* operator-(const Vector& a) const;
    Vector* subOn(int index, double numb) const;
    Vector* operator&(const Vector& a) const;
    Vector* operator*(const double &a) const;

    double& operator[](unsigned index) const;

    Vector& operator=(const Vector &a);

    friend std::ostream& operator<<(std::ostream &out, const Vector &item);

    ~Vector();
};

#endif  // INCLUDE_VECTOR_H_
