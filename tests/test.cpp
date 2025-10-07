#include <dynamical-system/dynamical-system.h>

#include <gtest/gtest.h>

TEST(TestDynamicalSystem, rosslerDefaults)
{
    dynamical_system::Rossler r;

    EXPECT_NEAR(0.2, r.a, 1e-6);
    EXPECT_NEAR(0.2, r.b, 1e-6);
    EXPECT_NEAR(5.7, r.c, 1e-6);
}

TEST(TestDynamicalSystem, rosslerCustom)
{
    dynamical_system::Rossler r(0.1, 0.1, 14.0);

    EXPECT_NEAR(0.1, r.a, 1e-6);
    EXPECT_NEAR(0.1, r.b, 1e-6);
    EXPECT_NEAR(14.0, r.c, 1e-6);
}

TEST(TestDynamicalSystem, lorenzDefaults)
{
    dynamical_system::Lorenz l;

    EXPECT_NEAR(10.0, l.sigma, 1e-6);
    EXPECT_NEAR(28.0, l.rho, 1e-6);
    EXPECT_NEAR(8.0 / 3.0, l.beta, 1e-6);
}
