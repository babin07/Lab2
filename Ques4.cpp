#include <iostream>
#include <vector>
#include <iomanip> // For setting precision

// Function to compute Newton's central divided difference interpolation
double newtonCentralInterpolation(const std::vector<double>& x, const std::vector<double>& y, double targetX) {
    int n = x.size();

    // Create a divided difference table
    std::vector<std::vector<double>> differenceTable(n, std::vector<double>(n, 0.0));

    // Initialize the first column with the given y-values
    for (int i = 0; i < n; i++) {
        differenceTable[i][0] = y[i];
    }

    // Fill the divided difference table
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            differenceTable[i][j] = (differenceTable[i + 1][j - 1] - differenceTable[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    // Display the divided difference table (optional, for verification)
    std::cout << "Divided Difference Table:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            std::cout << std::setw(10) << differenceTable[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Compute the interpolated value using the Newton's formula
    double result = differenceTable[0][0];
    double term = 1.0;

    for (int i = 1; i < n; i++) {
        term *= (targetX - x[i - 1]);
        result += term * differenceTable[0][i];
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

    // Perform Newton's central divided difference interpolation
    double interpolatedValue = newtonCentralInterpolation(x, y, targetX);

    // Display the result
    std::cout << "The approximated value of y at x = " << targetX << " is: " << interpolatedValue << std::endl;

    return 0;
}
