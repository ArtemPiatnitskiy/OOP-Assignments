#include <iostream>
#include "include/rectangle.h"
#include "include/point.h"
#include "include/arrayoffigures.h"

int main() {
    using namespace std;

    // Point p1(0.0, 0.0);
    // Point p2(3.0, 4.0); // rectangle 3x4 => area 12

    Point p1, p2;
    std::cin >> p1 >> p2;


    // Rectangle constructor has default description in header, so this works
    Rectangle r(p1, p2);
    cout << r << "\n";

    // Create container with small initial capacity to test resize/add
    ArrayOfFigures arr(2);
    arr.add_figure(r.clone());

    cout << "Array contents:\n";
    arr.print_figures(cout);

    cout << "Total square: " << arr.total_square() << "\n";

    // cleanup handled by ArrayOfFigures destructor
    return 0;
}