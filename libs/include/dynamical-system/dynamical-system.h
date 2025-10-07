#pragma once

#include <array>

namespace dynamical_system
{

using RosslerState = std::array<double, 3>;

struct Rossler
{
    explicit Rossler(double a = 0.2, double b = 0.2, double c = 5.7) :
        m_a(a),
        m_b(b),
        m_c(c)
    {
    }

    void operator()(const RosslerState &x, RosslerState &dx_dt, double /* t */) const
    {
        dx_dt[0] = -x[1] - x[2];
        dx_dt[1] = x[0] + m_a * x[1];
        dx_dt[2] = m_b + x[2] * (x[0] - m_c);
    }

    double m_a;
    double m_b;
    double m_c;
};

} // namespace dynamical_system
