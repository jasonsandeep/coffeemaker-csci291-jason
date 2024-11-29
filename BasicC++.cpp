#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// Function to display a floating-point number with fixed width and precision
void display_float(float num, int width, int precision);

// Template function to update the values based on a given factor
template <typename T>
void adjust_values(T &val1, T &val2, T factor = 10);

int main() {
    float x, y;

    // Get user input for two real numbers
    cout << "Enter two real numbers: ";
    cin >> x >> y;

    // Display the original numbers
    cout << "Initial numbers:\n";
    display_float(x, 7, 3);
    display_float(y, 7, 3);

    // Adjust the values using the adjust_values function
    adjust_values(x, y);

    // Display the updated numbers
    cout << "Modified numbers:\n";
    display_float(x, 7, 3);
    display_float(y, 7, 3);

    return 0;
}

// Function to print a real number with specified width and precision
void display_float(float num, int width, int precision) {
    cout << fixed << setw(width) << setprecision(precision) << num << endl;
}

// Template function to modify the values based on the sum and difference
template <typename T>
void adjust_values(T &val1, T &val2, T factor) {
    T temp1 = (val1 + val2) * factor;  // Calculate new value for val1
    T temp2 = (val1 - val2) * factor;  // Calculate new value for val2
    val1 = temp1;  // Update val1
    val2 = temp2;  // Update val2
}
