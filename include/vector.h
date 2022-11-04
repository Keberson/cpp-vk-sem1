#ifndef INCLUDE_VECTOR_H_
#define INCLUDE_VECTOR_H_

#include <iostream>

class Vector {
 private:
    double *_vector;
    size_t _len;
    bool _isVertical;

 public:
    Vector() : _vector(nullptr), _len(0), _isVertical(false) {}
    Vector(const Vector &old);
    explicit Vector(size_t len, bool isVertical) :
            _vector(new double[len]), _len(len), _isVertical(isVertical) {}
    Vector(std::initializer_list<double> list, bool isVertical);

    void reallocateMemory();
    size_t getLen() const;
    bool getVerticalState() const;
    void setLen(size_t len);
    void setVerticalState(bool isVertical);

    Vector operator+(const Vector& operand) const;
    Vector sumOn(size_t index, double numb) const;
    Vector operator-(const Vector& operand) const;
    Vector subOn(size_t index, double numb) const;
    Vector operator&(const Vector& operand) const;
    Vector operator*(const double& operand) const;

    double& operator[](size_t index) const;

    Vector& operator=(const Vector& operand);
    Vector& operator+=(const Vector& operand);
    Vector& operator-=(const Vector& operand);
    Vector& operator&=(const Vector& operand);

    friend std::ostream& operator<<(std::ostream &out, const Vector &item);

    ~Vector();
};

#endif  // INCLUDE_VECTOR_H_
