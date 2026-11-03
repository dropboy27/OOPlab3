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
    return size_;
}

bool QuadraticSet::empty() const
{
    return size_ == 0;
}

bool QuadraticSet::contains(const Quadratic &q) const
{
    size_t r = size_;
    size_t l = 0;
    while (l < r)
    {
        size_t mid = l + (r - l) / 2;
        if (q == data_[mid])
        {
            return true;
        }
        if (q < data_[mid])
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


bool QuadraticSet::add(const Quadratic& q){
    size_t r = size_;
    size_t l = 0;
    
    while (l < r)
    {
        size_t mid = l + (r - l) / 2;
        if (data_[mid] < q)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    size_t pos = l ;
    if(pos <size_ && data_[pos] == q){
        return false;
    }
    if (size_ == capacity_){
        if (size_ == 0){
            capacity_ = 1;
        }else{
            capacity_ = size_*2;
        }
        Quadratic *newdata = new Quadratic[capacity_];
        for(int i = 0; i <size_; i++){
            newdata[i]=data_[i];
        }
        
        delete[] data_;
        data_ = newdata;
    }
    
    for(size_t i = size_; i >pos; i--){
        data_[i] =data_[i-1]; 
    }
    size_++;
    data_[pos]=q;
    return true;
}

bool QuadraticSet::remove(const Quadratic& q){
    size_t r = size_;
    size_t l = 0;
    
    while (l < r)
    {
        size_t mid = l + (r - l) / 2;
        if (data_[mid] < q)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    size_t pos = l ;
    if (pos == size_ || !(data_[pos] == q))
    {
        return false;
    }
    for(size_t i = pos; i + 1 < size_; i++){
        data_[i] =data_[i+1]; 
    }
    size_--;
    return true;
}

bool QuadraticSet::operator()(const Quadratic& q)const{
    return contains(q);
}

QuadraticSet &QuadraticSet::operator+=(const Quadratic& q){
    add(q);
    return *this;
}

QuadraticSet &QuadraticSet::operator-=(const Quadratic& q){
    remove(q);
    return *this;
}

bool QuadraticSet::operator==(const QuadraticSet& other) const{
    if(size_!=other.size_){
        return false;
    }
    for(size_t i = 0; i <size_; i++){
        if (!(data_[i]==other.data_[i])){
            return false;
        }
    }
    return true;
}

bool QuadraticSet::operator!=(const QuadraticSet& other) const{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const QuadraticSet& set)
{
    os << '{';
    for (size_t i = 0; i < set.size_; i++)
    {
        if (i > 0)
        {
            os << ", ";
        }
        os << set.data_[i];
    }
    os << '}';
    return os;
}


QuadraticSet QuadraticSet::operator|(const QuadraticSet& other) const{
    QuadraticSet result{};
    for(int i = 0; i<size_; i++){
        result.add(data_[i]);
    }
    for(int i = 0; i<other.size_; i++){
        result.add(other.data_[i]);
    }
    return result;
}

QuadraticSet QuadraticSet::operator&(const QuadraticSet& other) const{
    QuadraticSet result{};
    size_t i =0;
    size_t j = 0;
    while(i < size_ && j<other.size_){
        if(data_[i] == other.data_[j]){
            result.add(data_[i]);
            i++;
            j++;
            continue;
        }
        if(data_[i] < other.data_[j]){
            i++;
        }else{
            j++;
        }
    }
    return result;
}
QuadraticSet QuadraticSet::operator-(const QuadraticSet& other) const{
    QuadraticSet result{};
    size_t i =0;
    size_t j = 0;
    while(i < size_ && j<other.size_){
        if(data_[i] == other.data_[j]){
            i++;
            j++;
            continue;
        }
        if(data_[i] < other.data_[j]){
            result.add(data_[i]);
            i++;
        }else{
            j++;
        }
    }
    for(size_t f =i; f<size_; f++){
        result.add(data_[f]);
    }
    return result;
}