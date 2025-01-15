#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Function to calculate the coefficients of least squares approximation for non-linear data
void leastSquaresNonLinear(const std::vector<double>& x, const std::vector<double>& y, double& a, double& b) {
    int n = x.size();

    double sumX = 0, sumLogY = 0, sumXLogY = 0, sumX2 = 0;

    // Compute the summations, taking the natural log of y
    for (int i = 0; i < n; i++) {
        double logY = std::log(y[i]);
        sumX += x[i];
        sumLogY += logY;
        sumXLogY += x[i] * logY;
        sumX2 += x[i] * x[i];
    }

    // Calculate coefficients a and b for ln(y) = ln(a) + b * x
    b = (n * sumXLogY - sumX * sumLogY) / (n * sumX2 - sumX * sumX);
    double lnA = (sumLogY - b * sumX) / n;
    a = std::exp(lnA); // Convert back from ln(a) to a
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

    double a, b;

    // Perform least squares approximation for non-linear data
    leastSquaresNonLinear(x, y, a, b);

    // Display the result
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "The exponential approximation is: y = " << a << " * e^(" << b << "x)" << std::endl;

    return 0;
}
