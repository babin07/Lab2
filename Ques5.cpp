#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

// Function to compute cubic spline interpolation
double cubicSplineInterpolation(const std::vector<double>& x, const std::vector<double>& y, double targetX) {
    int n = x.size() - 1; // Number of intervals
    std::vector<double> h(n), a(n + 1), b(n), d(n), c(n + 1, 0), alpha(n), l(n + 1, 1), mu(n + 1, 0), z(n + 1, 0);

    // Step 1: Compute h[i] and a[i]
    for (int i = 0; i < n; i++) {
        h[i] = x[i + 1] - x[i];
        a[i] = y[i];
    }
    a[n] = y[n];

    // Step 2: Compute alpha[i]
    for (int i = 1; i < n; i++) {
        alpha[i] = (3.0 / h[i]) * (a[i + 1] - a[i]) - (3.0 / h[i - 1]) * (a[i] - a[i - 1]);
    }

    // Step 3: Solve tridiagonal system for c[i]
    for (int i = 1; i < n; i++) {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1; // Boundary condition
    z[n] = 0; // Natural spline boundary condition
    c[n] = 0;

    for (int j = n - 1; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
    }

    // Step 4: Find the interval containing targetX
    int i = 0;
    while (i < n && !(x[i] <= targetX && targetX <= x[i + 1])) {
        i++;
    }

    // Step 5: Compute the interpolated value
    double dx = targetX - x[i];
    double result = a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;

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

    // Perform cubic spline interpolation
    double interpolatedValue = cubicSplineInterpolation(x, y, targetX);

    // Display the result
    std::cout << "The approximated value of y at x = " << targetX << " is: " << interpolatedValue << std::endl;

    return 0;
}
