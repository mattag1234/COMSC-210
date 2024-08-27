#include <iostream>
using namespace std;

int main()
{
    double r = 5.5;
    double h = 10.9;
    double area = 0;
    const double PI = 3.14159;

    // Compute the area of the cylinder
    area = 2 * PI * r * (r + h);
    cout << "The area of the cylinder is: " << area << endl;

    return 0;
}