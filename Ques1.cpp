#include <iostream>
#include <vector>

// Function to calculate Lagrange interpolation
double lagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y, double targetX) {
    int n = x.size();
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        // Calculate the Lagrange basis polynomial L_i(x)
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (targetX - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
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

    // Perform Lagrange interpolation
    double interpolatedValue = lagrangeInterpolation(x, y, targetX);

    // Display the result
    std::cout << "The approximated value of y at x = " << targetX << " is: " << interpolatedValue << std::endl;

    return 0;
}
