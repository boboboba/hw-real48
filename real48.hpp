#include <cstdint>
#include <cstring>

namespace math
{

class Real48
{
    char data[6];
public:
    // constructors
    constexpr Real48(): data{} {};
    Real48(const float number);
    Real48(const double number);
    constexpr Real48(const Real48& o) = default;

    // conversion operators
    operator float() const;
    operator double() const noexcept;

    // assignment operators
    Real48& operator=(const Real48& b) noexcept = default;
    Real48& operator+=(const Real48& b);
    Real48& operator-=(const Real48& b);
    Real48& operator*=(const Real48& b);
    Real48& operator/=(const Real48& b);

    // arithmetic operators
    Real48 operator+() const noexcept;
    Real48 operator-() const noexcept;
    Real48 operator+(const Real48& o) const;
    Real48 operator-(const Real48& o) const;
    Real48 operator*(const Real48& o) const;
    Real48 operator/(const Real48& o) const;

    // comparison operators
    bool operator>(const Real48& o) const noexcept;
    bool operator<(const Real48& o) const noexcept;

    // classify
    enum class Class
    {
        NORMAL,
        ZERO
    };
    Class Classify() const noexcept;

    // limits
    consteval static Real48 min()
    {
        Real48 t{};
        t.data[5] = 0x01;
        return t;
    }
    consteval static Real48 max()
    {
        Real48 t{};
        t.data[0] = 0xFF;
        t.data[1] = 0xFF;
        t.data[2] = 0xFF;
        t.data[3] = 0xFF;
        t.data[4] = 0x7F;
        t.data[5] = 0xFF;
        return t;
    }
    consteval static Real48 epsilon()
    {
        Real48 t{};
        t.data[0] = 0x01;
        t.data[5] = 0x81;
        return t;
    }

private:
};

} // namespace math
