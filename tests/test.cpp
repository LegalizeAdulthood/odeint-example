#include <dynamical-system/dynamical-system.h>

#include <gtest/gtest.h>

TEST(TestDynamicalSystem, rosslerDefaults)
{
    dynamical_system::Rossler r;

    EXPECT_NEAR(0.2, r.m_a, 1e-6);
    EXPECT_NEAR(0.2, r.m_b, 1e-6);
    EXPECT_NEAR(5.7, r.m_c, 1e-6);
}

TEST(TestDynamicalSystem, rosslerCustom)
{
    dynamical_system::Rossler r(0.1, 0.1, 14.0);

    EXPECT_NEAR(0.1, r.m_a, 1e-6);
    EXPECT_NEAR(0.1, r.m_b, 1e-6);
    EXPECT_NEAR(14.0, r.m_c, 1e-6);
}
