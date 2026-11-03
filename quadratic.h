#include <iostream>
#pragma once
class Quadratic
{
private:
    int a_, b_, c_;

public:
    Quadratic() : a_{0}, b_{0}, c_{0} {};
    Quadratic(int a, int b, int c) : a_{a}, b_{b}, c_{c} {};
    bool operator==(const Quadratic &other) const
    {
        return (this->a_ == other.a_ && this->b_ == other.b_ && this->c_ == other.c_);
    };
    bool operator<(const Quadratic &other) const
    {
        if (this->a_ != other.a_)
        {
            return this->a_ < other.a_;
        }
        if (this->b_ != other.b_)
        {
            return this->b_ < other.b_;
        }
        if (this->c_ != other.c_)
        {
            return this->c_ < other.c_;
        }
        return false;
    };
    friend std::ostream &operator<<(std::ostream &os, const Quadratic &q)
    {
        os << q.a_ << "x^2 + " << q.b_ << "x + " << q.c_;
        return os;
    };
};
