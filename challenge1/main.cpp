#include <iostream>
#include <vector>

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

int main()
{
    return 0;
}