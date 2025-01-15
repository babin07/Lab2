#include <iostream>
#include <vector>
#include <iomanip> // For setting precision

// Function to calculate the factorial of a number
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Function to compute Newton's backward difference interpolation
double newtonBackwardInterpolation(const std::vector<double>& x, const std::vector<double>& y, double targetX) {
    int n = x.size();

    // Create a difference table
    std::vector<std::vector<double>> differenceTable(n, std::vector<double>(n, 0.0));

    // Initialize the first column with the given y-values
    for (int i = 0; i < n; i++) {
        differenceTable[i][0] = y[i];
    }

    // Fill the backward difference table
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            differenceTable[i][j] = differenceTable[i][j - 1] - differenceTable[i - 1][j - 1];
        }
    }

    // Display the backward difference table (optional, for verification)
    std::cout << "Backward Difference Table:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << std::setw(10) << differenceTable[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Compute the interpolated value
    double h = x[1] - x[0]; // Assume equally spaced x values
    double p = (targetX - x[n - 1]) / h;
    double result = differenceTable[n - 1][0];
    double term = 1.0;

    for (int i = 1; i < n; i++) {
        term *= (p + (i - 1)) / i; // Update term for the current order
        result += term * differenceTable[n - 1][i];
    }

    return result;
}

int main() {
    int n;

    // Input the number of data points
    std::cout << "Enter the number of data points: ";
    std::cin >> n;

    std::vector<double> x(n), y(n);

    // Input data points
    std::cout << "Enter the data points (x and y) separated by space:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    double targetX;
    std::cout << "Enter the value of x to find the corresponding y: ";
    std::cin >> targetX;

    // Perform Newton's backward difference interpolation
    double interpolatedValue = newtonBackwardInterpolation(x, y, targetX);

    // Display the result
    std::cout << "The approximated value of y at x = " << targetX << " is: " << interpolatedValue << std::endl;

    return 0;
}
