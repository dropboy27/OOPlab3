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
    QuadraticSet &operator=(QuadraticSet &&other);
    size_t size() const;
    bool empty() const;
    bool contains(const Quadratic &q) const;
    bool add(const Quadratic& q);
    bool remove(const Quadratic&);
    bool operator()(const Quadratic& q) const;
    QuadraticSet& operator+=(const Quadratic& q);
    QuadraticSet& operator-=(const Quadratic& q);
    bool operator==(const QuadraticSet& other) const;
    bool operator!=(const QuadraticSet& other) const;
    friend std::ostream& operator<<(std::ostream& os, const QuadraticSet& set);
    QuadraticSet operator|(const QuadraticSet& other) const;
    QuadraticSet operator&(const QuadraticSet& other) const;
    QuadraticSet operator-(const QuadraticSet& other) const;
};