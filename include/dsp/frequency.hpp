#ifndef __DSP_FREQUENCY_HPP__
#define __DSP_FREQUENCY_HPP__

#include <cstddef>
#include <cstdint>
#include <ratio>
#include <chrono>

namespace dsp
{
    namespace internal
    {
        using custom_literal_integer_arg_type = unsigned long long;
    }

    template <typename _Rep, typename _Period>
    using frequency = std::chrono::duration<_Rep, _Period>;

    using nanohertz = frequency<std::int64_t, std::nano>;
    using microhertz = frequency<std::int64_t, std::micro>;
    using millihertz = frequency<std::int64_t, std::milli>;
    using hertz = frequency<std::int64_t, std::ratio<1>>;
    using kilohertz = frequency<std::int64_t, std::kilo>;
    using megahertz = frequency<std::int64_t, std::mega>;
    using gigahertz = frequency<std::int64_t, std::giga>;
    using terahertz = frequency<std::int64_t, std::tera>;

    namespace frequency_literals
    {
        [[nodiscard]] constexpr millihertz operator""_mHz(internal::custom_literal_integer_arg_type _Val) noexcept
        {
            return millihertz(_Val);
        }
        [[nodiscard]] constexpr hertz operator""_Hz(internal::custom_literal_integer_arg_type _Val) noexcept
        {
            return hertz(_Val);
        }
        [[nodiscard]] constexpr kilohertz operator""_KHz(internal::custom_literal_integer_arg_type _Val) noexcept
        {
            return kilohertz(_Val);
        }
        [[nodiscard]] constexpr megahertz operator""_MHz(internal::custom_literal_integer_arg_type _Val) noexcept
        {
            return megahertz(_Val);
        }
        [[nodiscard]] constexpr gigahertz operator""_GHz(internal::custom_literal_integer_arg_type _Val) noexcept
        {
            return gigahertz(_Val);
        }
    }

}

#endif