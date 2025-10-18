// #include <iostream>
// #include <sstream>
// #include <utility>
// #include "include/point.h"
// #include "include/rectangle.h"
// #include "include/trapezoid.h"
// #include "include/rhombus.h"
// #include "include/arrayoffigures.h"

// int main() {
//     using std::cout; using std::endl;

//     // --- Points ---
//     Point p1(0.0, 0.0);
//     Point p2(3.0, 0.0);
//     Point p3(3.0, 4.0);
//     Point p4(0.0, 4.0);

//     cout << "Points: " << p1 << " " << p2 << " " << p3 << " " << p4 << endl;

//     // --- Rectangle tests ---
//     Rectangle r1(p1, p3); // diagonal points
//     cout << "Rectangle r1:" << endl << r1 << endl;
//     cout << " center: " << r1.geometric_center() << endl;
//     cout << " square: " << r1.square() << " perimeter: " << r1.perimeter() << endl;
//     cout << " cast to double (area): " << static_cast<double>(r1) << endl;
//     cout << " r1 == r1: " << std::boolalpha << (r1 == r1) << endl;

//     // default-constructed rectangle + read from stream
//     Rectangle r2; // uses default ctor
//     std::istringstream rin("(0,0) (3,0) (3,4) (0,4)");
//     rin >> r2; // read 4 points
//     cout << "Rectangle r2 (read):" << endl << r2 << endl;
//     cout << " r1 <=> r2 compare (areas equal?): " << std::boolalpha << ((r1 == r2)) << endl;

//     // --- Trapezoid & Rhombus tests ---
//     Trapezoid t1(p1, p2, p3, p4);
//     cout << "Trapezoid t1:" << endl << t1 << endl;
//     cout << " t1 square: " << t1.square() << " perimeter: " << t1.perimeter() << endl;

//     Rhombus h1(p1, p2, p3, p4);
//     cout << "Rhombus h1:" << endl << h1 << endl;
//     cout << " h1 square: " << h1.square() << " perimeter: " << h1.perimeter() << endl;

//     // --- clone() tests ---
//     Figure* rc = r1.clone();
//     Figure* tc = t1.clone();
//     Figure* hc = h1.clone();
//     cout << "Cloned figures:" << endl;
//     cout << *rc << endl << *tc << endl << *hc << endl;
//     delete rc; delete tc; delete hc;

//     // --- ArrayOfFigures tests: add / print / total / remove ---
//     ArrayOfFigures arr(2);
//     arr.add_figure(r1.clone());
//     arr.add_figure(t1.clone());
//     arr.add_figure(h1.clone()); // triggers resize
//     cout << "Array after adds (size=" << arr.get_size() << ", cap=" << arr.get_capacity() << "):" << endl;
//     arr.print_figures(std::cout);
//     cout << "Total square: " << arr.total_square() << endl;

//     // copy-construction
//     ArrayOfFigures arr_copy = arr;
//     cout << "Copy constructed array (size=" << arr_copy.get_size() << "):" << endl;
//     arr_copy.print_figures(std::cout);

//     // move-construction
//     ArrayOfFigures arr_moved = std::move(arr);
//     cout << "Moved array (new owner size=" << arr_moved.get_size() << "), original size=" << arr.get_size() << endl;
//     arr_moved.print_figures(std::cout);

//     // copy-assignment
//     ArrayOfFigures arr_assign(1);
//     arr_assign = arr_copy;
//     cout << "After copy-assignment arr_assign size=" << arr_assign.get_size() << endl;

//     // move-assignment
//     ArrayOfFigures arr_move_assign(1);
//     arr_move_assign = std::move(arr_copy);
//     cout << "After move-assignment arr_move_assign size=" << arr_move_assign.get_size()
//          << ", arr_copy size=" << arr_copy.get_size() << endl;

//     // operator[] and remove
//     if (arr_moved.get_size() > 0) {
//         Figure* f0 = arr_moved[0];
//         cout << "First figure from arr_moved via operator[]:" << endl;
//         if (f0) cout << *f0 << endl;
//     }
//     if (arr_moved.get_size() > 1) {
//         cout << "Removing index 1 from arr_moved" << endl;
//         arr_moved.remove_figure(1);
//         cout << "After remove, size=" << arr_moved.get_size() << endl;
//         arr_moved.print_figures(std::cout);
//     }

//     // cleanup: destructors will free owned figures
//     cout << "All checks done." << endl;
//     return 0;
// }
// ```// filepath: /workspaces/OOP-Assignments/tasks/Laboratory_3/main.cpp
#include <iostream>
#include <sstream>
#include <utility>
#include "include/point.h"
#include "include/rectangle.h"
#include "include/trapezoid.h"
#include "include/rhombus.h"
#include "include/arrayoffigures.h"

int main() {
    using std::cout; using std::endl;

    // --- Points ---
    Point p1(0.0, 0.0);
    Point p2(3.0, 0.0);
    Point p3(3.0, 4.0);
    Point p4(0.0, 4.0);

    cout << "Points: " << p1 << " " << p2 << " " << p3 << " " << p4 << endl;

    // --- Rectangle tests ---
    Rectangle r1(p1, p3); // diagonal points
    cout << "Rectangle r1:" << endl << r1 << endl;
    cout << " center: " << r1.geometric_center() << endl;
    cout << " square: " << r1.square() << " perimeter: " << r1.perimeter() << endl;
    cout << " cast to double (area): " << static_cast<double>(r1) << endl;
    cout << " r1 == r1: " << std::boolalpha << (r1 == r1) << endl;

    // default-constructed rectangle + read from stream
    Rectangle r2; // uses default ctor
    std::istringstream rin("(0,0) (3,0) (3,4) (0,4)");
    rin >> r2; // read 4 points
    cout << "Rectangle r2 (read):" << endl << r2 << endl;
    cout << " r1 <=> r2 compare (areas equal?): " << std::boolalpha << ((r1 == r2)) << endl;

    // --- Trapezoid & Rhombus tests ---
    Trapezoid t1(p1, p2, p3, p4);
    cout << "Trapezoid t1:" << endl << t1 << endl;
    cout << " t1 square: " << t1.square() << " perimeter: " << t1.perimeter() << endl;

    Rhombus h1(p1, p2, p3, p4);
    cout << "Rhombus h1:" << endl << h1 << endl;
    cout << " h1 square: " << h1.square() << " perimeter: " << h1.perimeter() << endl;

    // --- clone() tests ---
    Figure* rc = r1.clone();
    Figure* tc = t1.clone();
    Figure* hc = h1.clone();
    cout << "Cloned figures:" << endl;
    cout << *rc << endl << *tc << endl << *hc << endl;
    delete rc; delete tc; delete hc;

    // --- ArrayOfFigures tests: add / print / total / remove ---
    ArrayOfFigures arr(2);
    arr.add_figure(r1.clone());
    arr.add_figure(t1.clone());
    arr.add_figure(h1.clone()); // triggers resize
    cout << "Array after adds (size=" << arr.get_size() << ", cap=" << arr.get_capacity() << "):" << endl;
    arr.print_figures(std::cout);
    cout << "Total square: " << arr.total_square() << endl;

    // copy-construction
    ArrayOfFigures arr_copy = arr;
    cout << "Copy constructed array (size=" << arr_copy.get_size() << "):" << endl;
    arr_copy.print_figures(std::cout);

    // move-construction
    ArrayOfFigures arr_moved = std::move(arr);
    cout << "Moved array (new owner size=" << arr_moved.get_size() << "), original size=" << arr.get_size() << endl;
    arr_moved.print_figures(std::cout);

    // copy-assignment
    ArrayOfFigures arr_assign(1);
    arr_assign = arr_copy;
    cout << "After copy-assignment arr_assign size=" << arr_assign.get_size() << endl;

    // move-assignment
    ArrayOfFigures arr_move_assign(1);
    arr_move_assign = std::move(arr_copy);
    cout << "After move-assignment arr_move_assign size=" << arr_move_assign.get_size()
         << ", arr_copy size=" << arr_copy.get_size() << endl;

    // operator[] and remove
    if (arr_moved.get_size() > 0) {
        Figure* f0 = arr_moved[0];
        cout << "First figure from arr_moved via operator[]:" << endl;
        if (f0) cout << *f0 << endl;
    }
    if (arr_moved.get_size() > 1) {
        cout << "Removing index 1 from arr_moved" << endl;
        arr_moved.remove_figure(1);
        cout << "After remove, size=" << arr_moved.get_size() << endl;
        arr_moved.print_figures(std::cout);
    }

    // cleanup: destructors will free owned figures
    cout << "All checks done." << endl;
    return 0;
}