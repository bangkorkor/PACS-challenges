#include <iostream>
#include <vector>
#include <cmath>

using Vec = std::vector<double>;
using Func = std::function<double(const Vec &)>; // function wrapper, I dont understand this syntax <double(const Vec&)>

struct parameters
{
    Vec x0;       // x0 (starting point) displayed as a vector
    double a0;    // alpha zero
    double eps_s; // s tolerances
    double eps_r; // r tolerances
    int kmax;     // maximum number of steps
    double sigma; // for Armijo rule
};

// --- gets the norm of a input vector
double norm(const Vec &v)
{
    double sum = 0.0;
    for (const auto &elm : v)
    {
        sum += elm * elm;
    }
    return std::sqrt(sum);
}

double armijo()
{
    return 0;
}

int main()
{
    parameters params = {{1, 1}, 0, 1e-6, 1e-6, 100, 0.25}; // {{x0}, a0, eps_s, eps_r, kmax, sigma}
    Func F = [](const Vec &x) -> double
    {
        return x[0] * x[1] + 4 * x[0] * x[0] * x[0] * x[0] + x[1] * x[1] + 3 * x[0]; // f(x,y) = xy + 4*x^4 + y^2 + 3*x
    };

    Vec vec1 = {5, 2.0, 4.1, 3.6};
    for (double i : vec1)
    {
        std::cout << i << "\n";
    }

    double norm1 = norm(vec1);
    std::cout << norm1 << "\n";

    return 0;
}