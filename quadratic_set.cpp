#include "quadratic_set.h"
#include "quadratic.h"
#include <iostream>
QuadraticSet::QuadraticSet()
{
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
};

QuadraticSet::QuadraticSet(const QuadraticSet &other)
{
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    this->data_ = new Quadratic[this->capacity_];
    for (size_t i = 0; i < size_; i++)
    {
        this->data_[i] = other.data_[i];
    }
}
void QuadraticSet::swap(QuadraticSet &other) noexcept
{
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->size_, other.size_);
    std::swap(this->data_, other.data_);
}

QuadraticSet::QuadraticSet(QuadraticSet &&other) noexcept
{
    this->data_ = nullptr;
    this->capacity_ = 0;
    this->size_ = 0;
    QuadraticSet::swap(other);
}
QuadraticSet &QuadraticSet::operator=(const QuadraticSet &other)
{
    QuadraticSet tmp(other);
    QuadraticSet::swap(tmp);
    return *this;
}

QuadraticSet &QuadraticSet::operator=(QuadraticSet &&other)
{
    if (this != &other)
    {
        QuadraticSet::swap(other);
        delete[] other.data_;
        other.capacity_ = 0;
        other.size_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

QuadraticSet::~QuadraticSet()
{
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

size_t QuadraticSet::size() const
{
    return this->size_;
}

bool QuadraticSet::empty() const
{
    return this->size_ == 0;
}

bool QuadraticSet::contains(const Quadratic &q) const
{
    size_t r = this->size_;
    size_t l = 0;
    while (l < r)
    {
        size_t mid = l + (r - l) / 2;
        if (q == this->data_[mid])
        {
            return true;
        }
        if (q < this->data_[mid])
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return false;
}
