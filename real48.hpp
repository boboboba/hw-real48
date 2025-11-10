namespace math
{

class Real48
{
public:
    // constructors
    constexpr Real48(); // TODO: add definition
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
    consteval static Real48 min();     // TODO: add definition
    consteval static Real48 max();     // TODO: add definition
    consteval static Real48 epsilon(); // TODO: add definition

private:
    // TODO: add members
};

} // namespace math
