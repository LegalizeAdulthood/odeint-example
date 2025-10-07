#pragma once

#include <array>

namespace dynamical_system
{

using RosslerState = std::array<double, 3>;

struct Rossler
{
    explicit Rossler(double a = 0.2, double b = 0.2, double c = 5.7) :
        a(a),
        b(b),
        c(c)
    {
    }

    void operator()(const RosslerState &x, RosslerState &dx_dt, double /* t */) const
    {
        dx_dt[0] = -x[1] - x[2];
        dx_dt[1] = x[0] + a * x[1];
        dx_dt[2] = b + x[2] * (x[0] - c);
    }

    double a;
    double b;
    double c;
};

using LorenzState = std::array<double, 3>;

struct Lorenz
{
    explicit Lorenz(double sigma = 10.0, double rho = 28.0, double beta = 8.0 / 3.0) :
        sigma(sigma),
        rho(rho),
        beta(beta)
    {
    }

    void operator()(const LorenzState &x, LorenzState &dx_dt, double /* t */) const
    {
        dx_dt[0] = sigma * (x[1] - x[0]);
        dx_dt[1] = x[0] * (rho - x[2]) - x[1];
        dx_dt[2] = x[0] * x[1] - beta * x[2];
    }

    double sigma;
    double rho;
    double beta;
};

} // namespace dynamical_system
