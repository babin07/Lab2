#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

// Function to solve the normal equations for polynomial least squares
void solveNormalEquations(const std::vector<std::vector<double>>& matrix, std::vector<double>& coefficients, int degree) {
    int n = degree + 1;
    std::vector<double> result(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[j][i] != 0) {
                double ratio = matrix[j][i] / matrix[i][i];
                for (int k = i; k <= n; k++) {
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        result[i] = matrix[i][n] / matrix[i][i];
        for (int j = 0; j < i; j++) {
            matrix[j][n] -= matrix[j][i] * result[i];
        }
    }

    coefficients = result;
}

// Function to calculate least squares approximation for polynomial data
void leastSquaresPolynomial(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& coefficients, int degree) {
    int n = x.size();
    int m = degree + 1;

    std::vector<std::vector<double>> matrix(m, std::vector<double>(m + 1, 0));

    // Construct the normal equations
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                matrix[i][j] += std::pow(x[k], i + j);
            }
        }
        for (int k = 0; k < n; k++) {
            matrix[i][m] += std::pow(x[k], i) * y[k];
        }
    }

    // Solve the system of linear equations
    solveNormalEquations(matrix, coefficients, degree);
}

int main() {
    int n, degree;

    // Input the number of data points
    std::cout << "Enter the number of data points: ";
    std::cin >> n;

    std::vector<double> x(n), y(n);

    // Input data points
    std::cout << "Enter the data points (x and y) separated by space:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    // Input the degree of the polynomial
    std::cout << "Enter the degree of the polynomial: ";
    std::cin >> degree;

    std::vector<double> coefficients;

    // Perform least squares approximation for polynomial data
    leastSquaresPolynomial(x, y, coefficients, degree);

    // Display the result
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "The polynomial approximation is: y = ";
    for (int i = 0; i <= degree; i++) {
        if (i > 0) {
            std::cout << " + ";
        }
        std::cout << coefficients[i] << "x^" << i;
    }
    std::cout << std::endl;

    return 0;
}
