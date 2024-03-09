#include <iostream>
#include <vector>
#include <cmath>

using Vec = std::vector<double>;

struct parameters
{
    Vec x0;
    double a0;
    double eps_s;
    double eps_r;
    int kmax;
    double sigma; // for Armijo rule
};

double norm(const Vec &v)
{
    double sum = 0.0;
    for (const auto &elm : v)
    {
        sum += elm * elm;
    }
    return std::sqrt(sum);
}

int main()
{
    Vec vec1 = {2.0, -2.0};

    for (double i : vec1)
    {
        std::cout << i << "\n";
    }

    double norm1 = norm(vec1);
    std::cout << norm1;

    return 0;
}