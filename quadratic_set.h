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
    bool QuadraticSet::add(const Quadratic& q);
    bool remove(const Quadratic&);
    bool QuadraticSet::operator()(const Quadratic& q) const;
    QuadraticSet& QuadraticSet::operator+=(const Quadratic& q);
    QuadraticSet& QuadraticSet::operator-=(const Quadratic& q);
    bool QuadraticSet::operator==(const QuadraticSet& other) const;
    bool QuadraticSet::operator!=(const QuadraticSet& other) const;
    friend std::ostream& operator<<(std::ostream& os, const QuadraticSet& set);
    QuadraticSet QuadraticSet::operator|(const QuadraticSet& other) const;
    QuadraticSet QuadraticSet::operator&(const QuadraticSet& other) const;
    QuadraticSet QuadraticSet::operator-(const QuadraticSet& other) const;
};