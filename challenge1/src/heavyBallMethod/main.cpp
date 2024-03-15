#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

using Vec = std::vector<double>;
using Func = std::function<double(const Vec &)>;
using GradFunc = std::function<Vec(const Vec &)>;

struct Parameters
{
    Vec x0;       // initial posision
    double a0;    // initial alpha
    double eps_s; // s tolerances
    double eps_r; // r tolerances
    int kmax;     // maximum number of steps
    double eta;   // memory parameter
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

// --- computes the minimum of a function usinng heavy ball method
Vec heavyBallMethod(Func f, GradFunc grad_f, const Parameters &params)
{
    Vec xk = params.x0;    // x0
    Vec grad = grad_f(xk); // grad = ∇f(xk)
    Vec dk(xk.size());
    for (int i = 0; i < xk.size(); ++i)
    {
        dk[i] = xk[i] - params.a0 * grad[i];
    }

    int k = 0;
    while (k < params.kmax)
    {

        Vec x_next(xk.size());
        for (int i = 0; i < xk.size(); ++i)
        {
            x_next[i] = xk[i] + dk[i];
        }

        Vec grad_next = grad_f(x_next);

        Vec d_next(dk.size());
        for (int i = 0; i < dk.size(); ++i)
        {
            d_next[i] = params.eta * dk[i] - params.a0 * grad_next[i];
        }

        // stopping conditions
        if (norm(x_next) - norm(xk) < params.eps_s || std::abs(f(x_next) - f(xk)) < params.eps_r)
        {
            return x_next;
        }
        xk = x_next;
        dk = d_next;
        ++k;
        std::cout << "iteration numer " << k << "\n";
        std::cout << "Minimum found at: (" << xk[0] << ", " << xk[1] << ")\n";
        std::cout << "Function value at minimum: " << f(xk) << "\n";
    }
    std::cout << "no convergence, kmax reached"
              << "\n";

    return xk;
}

int main()
{

    Parameters params = {{0, 0}, 0.001, 1e-6, 1e-6, 1000, 0.79}; // {{x0}, a0, eps_s, eps_r, kmax, eta}

    // --- test case
    Func f = [](const Vec &x) -> double
    {
        return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0]; // f(x,y) = x*y + 4*x^4 + y^2 + 3*x
    };

    GradFunc grad_f = [](const Vec &x) -> Vec
    {
        return {16 * pow(x[0], 3) + x[1] + 3, x[0] + 2 * x[1]}; // gradF = {y + 16*x^3 + 3, x + 2*y}
    };

    Vec min_point_f = heavyBallMethod(f, grad_f, params);
    std::cout << "---------\n";
    std::cout << "Minimum found at: (" << min_point_f[0] << ", " << min_point_f[1] << ")\n";
    std::cout << "Function value at minimum: " << f(min_point_f) << std::endl;

    return 0;
}