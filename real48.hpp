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
    consteval static Real48 min(){
        math::Real48 temp{};
        temp.data[5] = 1;
        return temp;
    }
    consteval static Real48 max(){
        math::Real48 temp{};
        constexpr uint64_t bits = ~(~0ULL << 48);
        std::memcpy(&temp, &bits, 6);
        return temp;
    }
    consteval static Real48 epsilon(){
        math::Real48 temp{};
        temp.data[4] = 0b01010010;
        temp.data[5] = -1;
        return temp;
    }

private:
};

} // namespace math
