#include "dynamical-system/dynamical-system.h"

#include <boost/numeric/odeint.hpp>

namespace dynamical_system
{

Orbit iterate(System system, const Point3d &initial, double dt, int steps)
{
    Orbit orbit;
    const auto push_point = [&orbit](const Point3d &x, const double /* t */)
    {
        orbit.emplace_back(x);
    };

    Point3d state{initial};
    switch (system)
    {
    case System::NONE:
        break;

    case System::LORENZ:
    {
        Lorenz lorenz;
        boost::numeric::odeint::integrate(lorenz, state, 0.0, dt * steps, dt, push_point);
        break;
    }

    case System::ROSSLER:
    {
        Rossler rossler;
        boost::numeric::odeint::integrate(rossler, state, 0.0, dt * steps, dt, push_point);
        break;
    }
    }

    return orbit;
}

} // namespace dynamical_system
