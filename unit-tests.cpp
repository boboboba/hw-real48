#include "real48.hpp"

#include "gtest/gtest.h"
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>

using math::Real48;

static_assert(sizeof(Real48) == 6);

namespace
{

#pragma pack(push, 1)
struct Binary48
{
    std::uint8_t exponent;
    std::uint64_t fraction   : 39;
    std::uint8_t significand : 1;
};
#pragma pack(pop)

static_assert(sizeof(Real48) == sizeof(Binary48));

} // namespace

TEST(DeafultCtorTest, ProducesNull)
{
    const Real48 n {};
    EXPECT_EQ(n.Classify(), Real48::Class::ZERO);
    Binary48 b48 {};
    std::memcpy(&b48, &n, sizeof(n));
    EXPECT_EQ(b48.exponent, 0);
}

TEST(FromFloatCtor, ThrowsOverflow)
{
    const std::array inputs = {
        std::nanf(""),
        std::nanf("1"),
        std::nanf("2"),
        std::numeric_limits<float>::infinity(),
        -std::numeric_limits<float>::infinity()
    };
    for (const auto n : inputs)
    {
        EXPECT_THROW(Real48 {n}, std::overflow_error) << "Testing: " << n;
    }
}

TEST(FromFloatCtor, ProducesPositiveNull)
{
    const std::array inputs = {
        0.f,
        -0.f,
        std::numeric_limits<float>::denorm_min(),
        -std::numeric_limits<float>::denorm_min()
    };
    for (const auto n : inputs)
    {
        const Real48 r48 {n};
        EXPECT_EQ(r48.Classify(), Real48::Class::ZERO);
        Binary48 b48 {};
        std::memcpy(&b48, &r48, sizeof(n));
        EXPECT_EQ(b48.exponent, 0);
        EXPECT_EQ(b48.significand, 0);
    }
}

TEST(FromFloatCtor, ValidInputs)
{
    const std::array inputs = {
        float {1e-37},
        float {1e+38},
        float {-1e-37},
        float {-1e38},
        float {1.123456789e5},
        float {-1.123456789e5},
        float {1},
        float {-1}
    };
    for (const auto n : inputs)
    {
        const Real48 r48 {n};
        EXPECT_EQ(r48.Classify(), Real48::Class::NORMAL) << "Testing: " << n;
    }
}

TEST(FromDoubleCtor, ThrowsOverflow)
{
    const std::array inputs = {
        std::nan(""),
        std::nan("1"),
        std::nan("2"),
        std::numeric_limits<double>::infinity(),
        -std::numeric_limits<double>::infinity(),
        1e39,
        1e-39,
        1e100,
        1e-100
    };
    for (const auto n : inputs)
    {
        EXPECT_THROW(Real48 {n}, std::overflow_error) << "Testing: " << n;
    }
}

TEST(FromDoubleCtor, ProducesPositiveNull)
{
    const std::array inputs = {
        0.,
        -0.,
        std::numeric_limits<double>::denorm_min(),
        -std::numeric_limits<double>::denorm_min()
    };
    for (const auto n : inputs)
    {
        const Real48 r48 {n};
        EXPECT_EQ(r48.Classify(), Real48::Class::ZERO);
        Binary48 b48 {};
        std::memcpy(&b48, &r48, sizeof(r48));
        EXPECT_EQ(b48.exponent, 0);
        EXPECT_EQ(b48.significand, 0);
    }
}

TEST(FromDoubleCtor, ValidInputs)
{
    const std::array inputs = {
        double {1e-37},
        double {1e+38},
        double {-1e-37},
        double {-1e38},
        double {1.123456789e5},
        double {-1.123456789e5},
        double {1},
        double {-1}
    };
    for (const auto n : inputs)
    {
        const Real48 r48 {n};
        EXPECT_EQ(r48.Classify(), Real48::Class::NORMAL) << "Testing: " << n;
    }
}

TEST(ConversionToFloatTest, Zero)
{
    const Real48 n {};
    EXPECT_EQ(float {n}, 0.f);
}

TEST(ConversionToFloatTest, ValidInputs)
{
    const std::array inputs = {
        float {2},
        float {-2},
        float {1e-10},
        float {1e10},
        float {-1e-10},
        float {-1e10}
    };
    for (const auto n : inputs)
    {
        const Real48 r48 {n};
        EXPECT_NO_THROW((void)float {r48}) << "Testing: " << n;
        EXPECT_NEAR(float {r48}, n, std::abs(n / 100)) << "Testing: " << n;
    }
}

TEST(ConversionToDoubleTest, Zero)
{
    const Real48 n {};
    EXPECT_EQ(double {n}, 0.f);
}

TEST(ConversionToDoubleTest, ValidInputs)
{
    const std::array inputs = {
        double {2},
        double {-2},
        double {1e-30},
        double {1e30},
        double {-1e-30},
        double {-1e30}
    };
    for (const auto n : inputs)
    {
        const Real48 r48 {n};
        EXPECT_NO_THROW((void)double {r48}) << "Testing: " << n;
        EXPECT_NEAR(double {r48}, n, std::abs(n / 100)) << "Testing: " << n;
    }
}

TEST(CopyAssignmentOperatorTest, ProducesSameValue)
{
    const Real48 lhs {1.0};
    Real48 rhs {2.0};

    EXPECT_NO_THROW(rhs = lhs);
    EXPECT_EQ(std::memcmp(&lhs, &rhs, sizeof(Real48)), 0);
}

TEST(AdditionAssignemtnOperatorTest, ProducesSum)
{
    const Real48 lhs {1.0};
    Real48 rhs {2.0};

    EXPECT_NO_THROW(rhs += lhs);
    EXPECT_NEAR(double {rhs}, 3.0, 3.0 / 100);
}

TEST(SubtractionAssignemtnOperatorTest, ProducesSum)
{
    const Real48 lhs {2.0};
    Real48 rhs {1.0};

    EXPECT_NO_THROW(rhs -= lhs);
    EXPECT_NEAR(double {rhs}, -1.0, 1.0 / 100);
}

TEST(MultiplicationAssignemtnOperatorTest, ProducesSum)
{
    const Real48 lhs {2.0};
    Real48 rhs {3.0};

    EXPECT_NO_THROW(rhs *= lhs);
    EXPECT_NEAR(double {rhs}, 6.0, 6.0 / 100);
}

TEST(DivisionAssignemtnOperatorTest, ProducesSum)
{
    const Real48 lhs {2.0};
    Real48 rhs {3.0};

    EXPECT_NO_THROW(rhs /= lhs);
    EXPECT_NEAR(double {rhs}, 1.5, 1.5 / 100);
}

TEST(UnaryPlusOperatorTest, ProducesSameValue)
{
    const Real48 positive {1.0};
    const Real48 negative {-1.0};

    EXPECT_NEAR(double {+positive}, 1.0, 1.0 / 100);
    EXPECT_NEAR(double {+negative}, -1.0, 1.0 / 100);
}

TEST(UnaryMinusOperatorTest, ProducesNegativeValue)
{
    const Real48 positive {1.0};
    const Real48 negative {-1.0};

    EXPECT_NEAR(double {-positive}, -1.0, 1.0 / 100);
    EXPECT_NEAR(double {-negative}, 1.0, 1.0 / 100);
}

TEST(AdditionOperatorTest, ProducesSum)
{
    const Real48 lhs {2.0};
    const Real48 rhs {-3.0};

    EXPECT_NO_THROW(lhs + rhs);
    EXPECT_NEAR(double {lhs + rhs}, -1.0, 1.0 / 100);
}

TEST(SubtractionOperatorTest, ProducesSum)
{
    const Real48 lhs {2.0};
    const Real48 rhs {-3.0};

    EXPECT_NO_THROW(lhs - rhs);
    EXPECT_NEAR(double {lhs - rhs}, 5.0, 5.0 / 100);
}

TEST(MultiplicationOperatorTest, ProducesSum)
{
    const Real48 lhs {2.0};
    const Real48 rhs {-3.0};

    EXPECT_NO_THROW(lhs * rhs);
    EXPECT_NEAR(double {lhs * rhs}, -6.0, 6.0 / 100);
}

TEST(DivisionOperatorTest, ProducesSum)
{
    const Real48 lhs {2.0};
    const Real48 rhs {-3.0};

    EXPECT_NO_THROW(lhs / rhs);
    EXPECT_NEAR(double {lhs / rhs}, -0.666666, 0.000001);
}

TEST(LessThanOperatorTest, CorrectEvaluation)
{
    const Real48 lhs {2.0};
    const Real48 rhs {-3.0};

    EXPECT_NO_THROW((void)(lhs < rhs));
    EXPECT_FALSE(lhs < rhs);
}

TEST(GreaterThanOperatorTest, CorrectEvaluation)
{
    const Real48 lhs {2.0};
    const Real48 rhs {-3.0};

    EXPECT_NO_THROW((void)(lhs > rhs));
    EXPECT_TRUE(lhs > rhs);
}

TEST(MinTest, CorrectEvaluation)
{
    constexpr auto min = Real48::min();
    EXPECT_NEAR(double {min}, std::pow(2, -128), std::pow(2, -130));
}

TEST(MaxTest, CorrectEvaluation)
{
    constexpr auto max = Real48::max();
    EXPECT_NEAR(double {max}, std::pow(2, 126) * 2, std::pow(2, 124));
}

TEST(EpsilonTest, CorrectEvaluation)
{
    constexpr auto eps = Real48::epsilon();
    EXPECT_NEAR(double {eps}, std::pow(2, -39), std::pow(2, -41));
}
