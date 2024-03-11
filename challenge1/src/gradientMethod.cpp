#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

using Vec = std::vector<double>;
using Func = std::function<double(const Vec &)>; // function wrapper, I dont understand this syntax <double(const Vec&)>
using GradFunc = std::function<Vec(const Vec &)>;

struct Parameters
{
    Vec x0;       // initial posision
    double a0;    // initial alpha
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

double armijo(const Parameters &params, Func &f, const Vec &grad_f, const Vec &xk)
{
    double alpha = params.a0;
    Vec x_next(xk.size()); // x_next is (xk − α0∇f(xk)), initializes x_next with the same size as xk,
    do
    {
        for (int i = 0; i < xk.size(); ++i)
        {
            x_next[i] = xk[i] - alpha * grad_f[i]; // grad = ∇f(xk)
        }
        if (f(xk) - f(x_next) >= params.sigma * alpha * norm(grad_f) * norm(grad_f))
            break;
        alpha /= 2;
        std::cout << "lowering alpha\n";
    } while (true);
    return alpha;
}

Vec gradientDecent(Func f, GradFunc grad_f, const Parameters &params)
{
    Vec xk = params.x0;
    int k = 0; // number of iterations
    while (k < params.kmax)
    {
        Vec grad = grad_f(xk); // grad = ∇f(xk)
        double alpha = armijo(params, f, grad, xk);

        Vec x_next(xk.size());
        for (int i = 0; i < xk.size(); ++i)
        {
            x_next[i] = xk[i] - alpha * grad[i];
        }

        if (norm(x_next) - norm(xk) < params.eps_s || std::abs(f(x_next) - f(xk)) < params.eps_r)
        {
            return x_next;
        }
        xk = x_next; // housekeeping update xk
        ++k;
        std::cout << "iteration numer " << k << "\n";
        std::cout << "Minimum found at: (" << xk[0] << ", " << xk[1] << ")\n";
        std::cout << "Function value at minimum: " << f(xk) << std::endl;
        std::cout << "alpha is " << alpha << "\n\n";
    }
    std::cout << "no convergence, kmax reached"
              << "\n";
    return xk; // No convergence, k > kmax reached
}

int main()
{
    Parameters params = {{0, 0}, 0.01, 1e-6, 1e-6, 1000, 0.45}; // {{x0}, a0, eps_s, eps_r, kmax, sigma}

    // --- simple example f(x) = x^2 - 3x + 2
    // Func g = [](const Vec &x) -> double
    // {
    //     return x[0] * x[0] - 3 * x[0] + 2;
    // };

    // GradFunc grad_g = [](const Vec &x) -> Vec
    // {
    //     return {2 * x[0] - 3}; // gradF = {2x -3}
    // };

    // Vec min_point_g = gradientDecent(g, grad_g, params);
    // std::cout << "Minimum found at: (" << min_point_g[0] << ")\n";
    // std::cout << "Function value at minimum: " << g(min_point_g) << std::endl;

    // --- test case
    Func f = [](const Vec &x) -> double
    {
        return x[0] * x[1] + 4 * x[0] * x[0] * x[0] * x[0] + x[1] * x[1] + 3 * x[0]; // f(x,y) = xy + 4*x^4 + y^2 + 3*x
    };

    GradFunc grad_f = [](const Vec &x) -> Vec
    {
        return {x[1] + 16 * x[0] * x[0] * x[0] + 3, x[0] + 2 * x[1]}; // gradF = {y + 16*x^3 + 3, x + 2*y}
    };

    Vec min_point_f = gradientDecent(f, grad_f, params);
    std::cout << "Minimum found at: (" << min_point_f[0] << ", " << min_point_f[1] << ")\n";
    std::cout << "Function value at minimum: " << f(min_point_f) << std::endl;

    return 0;
}