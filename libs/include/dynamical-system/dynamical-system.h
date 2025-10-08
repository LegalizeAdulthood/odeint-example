#pragma once

#include <array>
#include <vector>

namespace dynamical_system
{

enum class Attractor
{
    NONE = 0,
    LORENZ = 1,
    ROSSLER = 2
};

using Point3f = std::array<float, 3>;

struct Rossler
{
    explicit Rossler(float a = 0.2, float b = 0.2, float c = 5.7) :
        a(a),
        b(b),
        c(c)
    {
    }

    void operator()(const Point3f &x, Point3f &dx_dt, float /* t */) const
    {
        dx_dt[0] = -x[1] - x[2];
        dx_dt[1] = x[0] + a * x[1];
        dx_dt[2] = b + x[2] * (x[0] - c);
    }

    float a;
    float b;
    float c;
};

struct Lorenz
{
    explicit Lorenz(float sigma = 10.0, float rho = 28.0, float beta = 8.0 / 3.0) :
        sigma(sigma),
        rho(rho),
        beta(beta)
    {
    }

    void operator()(const Point3f &x, Point3f &dx_dt, float /* t */) const
    {
        dx_dt[0] = sigma * (x[1] - x[0]);
        dx_dt[1] = x[0] * (rho - x[2]) - x[1];
        dx_dt[2] = x[0] * x[1] - beta * x[2];
    }

    float sigma;
    float rho;
    float beta;
};

using Orbit = std::vector<Point3f>;

Orbit iterate(Attractor system, const Point3f &initial, float begin, float end, float dt);

} // namespace dynamical_system
