#include "dynamical-system/dynamical-system.h"

#include <boost/numeric/odeint.hpp>

namespace dynamical_system
{

Orbit iterate( System system, const Point3f &initial, float begin, float end, float dt )
{
    Orbit orbit;
    const auto push_point = [&orbit](const Point3f &x, const float /* t */)
    {
        orbit.emplace_back(x);
    };

    Point3f state{initial};
    switch (system)
    {
    case System::NONE:
        break;

    case System::LORENZ:
    {
        Lorenz lorenz;
        boost::numeric::odeint::integrate(lorenz, state, begin, end, dt, push_point);
        break;
    }

    case System::ROSSLER:
    {
        Rossler rossler;
        boost::numeric::odeint::integrate(rossler, state, begin, end, dt, push_point);
        break;
    }
    }

    return orbit;
}

} // namespace dynamical_system
