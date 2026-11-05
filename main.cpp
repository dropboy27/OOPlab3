#include <iostream>
#include "quadratic_set.h"
using namespace std;

int main()
{
    QuadraticSet a, b;
    a.add(Quadratic(1, 2, 3));
    a += Quadratic(2, 0, 1);
    b.add(Quadratic(2, 0, 1));
    b.add(Quadratic(3, 1, 0));
    cout << "A: " << a << '\n';
    cout << "B: " << b << '\n';
    cout << "Size: " << a.size() << ", empty: " << a.empty() << '\n';
    cout << "Contains (1, 2, 3): " << a.contains(Quadratic(1, 2, 3)) << '\n';
    cout << "Union: " << (a | b) << '\n';
    cout << "Intersection: " << (a & b) << '\n';
    cout << "Difference: " << (a - b) << '\n';
    a.remove(Quadratic(1, 2, 3));
    cout << "After remove: " << a << '\n';
}
