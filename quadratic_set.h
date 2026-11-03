#include <iostream>
#include "quadratic.h"
#pragma once
class QuadraticSet
{
private:
    Quadratic *data_;
    size_t size_;
    size_t capacity_;

public:
    QuadraticSet();
    ~QuadraticSet();
    void swap(QuadraticSet &other) noexcept;
    QuadraticSet &operator=(const QuadraticSet &other);
    QuadraticSet(const QuadraticSet &other);
    QuadraticSet(QuadraticSet &&other) noexcept;
    QuadraticSet &QuadraticSet::operator=(QuadraticSet &&other);
    size_t QuadraticSet::size() const;
    bool QuadraticSet::empty() const;
    bool QuadraticSet::contains(const Quadratic &q) const;
};