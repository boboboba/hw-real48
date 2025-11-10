#include "real48.hpp"

#include <cstring>
#include <print>
#include <stdexcept>

extern "C" int
LLVMFuzzerTestOneInput(const std::uint8_t* data, std::size_t size)
{
    if (size < sizeof(float))
    {
    }
    else if (size < sizeof(double))
    {
        try
        {
            float input {};
            std::memcpy(&input, data, sizeof(input));
            std::println("from float: {}", input);
            math::Real48 r48 {input};
        }
        catch (const std::overflow_error& err)
        {
        }
    }
    else
    {
        try
        {
            double input {};
            std::memcpy(&input, data, sizeof(input));
            std::println("from float: {}", input);
            math::Real48 r48 {input};
        }
        catch (const std::overflow_error& err)
        {
        }
    }
    return 0;
}
