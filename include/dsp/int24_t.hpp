#ifndef __DSP_INT24_T_HPP__
#define __DSP_INT24_T_HPP__

#include <iostream>

#include <cstdint>
#include <cstddef>
#include <array>
#include <bit>
#include <type_traits>

namespace dsp
{

#pragma pack(push, 1)
struct threebytes
{
	using default_signed_char_type = signed char;
	using default_char_type = char;
	using default_unsigned_char_type = unsigned char;
	using default_signed_short_type = signed short;
	using default_unsigned_short_type = unsigned short;
	using default_signed_int_type = signed int;
	using default_unsigned_int_type = unsigned int;
	using default_signed_long_type = signed long;
	using default_unsigned_long_type = unsigned long;
	using default_signed_long_long_type = signed long long;
	using default_unsigned_long_long_type = unsigned long long;

	using default_float_type = float;
	using default_double_type = double;
	using default_long_double_type = long double;

public:
    threebytes() = default;

    threebytes(default_signed_int_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
    }

    threebytes(default_unsigned_int_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
    }

    threebytes(default_signed_long_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
    }

    threebytes(default_unsigned_long_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
    }

    /*constexpr threebytes(default_signed_long_type value)
    {
        *this = static_cast<threebytes>(value);
    }

    constexpr threebytes(default_unsigned_long_type value)
    {
        *this = static_cast<threebytes>(value);
    }*/

    explicit threebytes(default_float_type value)
    {
        *this = static_cast<default_signed_int_type>(value);
    }
    explicit threebytes(default_double_type value)
    {
        *this = static_cast<default_signed_int_type>(value);
    }

    explicit threebytes(default_long_double_type value)
    {
        *this = static_cast<default_signed_int_type>(value);
    }




    threebytes& operator=(default_signed_int_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
        return *this;
    }

    threebytes& operator=(default_unsigned_int_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
        return *this;
    }

    threebytes& operator=(default_signed_long_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
        return *this;
    }

    threebytes& operator=(default_unsigned_long_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
        return *this;
    }

    threebytes& operator=(default_signed_long_long_type value)
    {
        this->bytes_[0] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[0];
        this->bytes_[1] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[1];
        this->bytes_[2] = reinterpret_cast<decltype(this->bytes_)::pointer>(&value)[2];
        return *this;
    }




    constexpr threebytes& operator=(default_unsigned_long_long_type value)
    {
        *this = value;
        return *this;
    }

    constexpr explicit operator bool() const
    {
        return *this;
    }

    constexpr explicit operator char() const
    {
        return *this;
    }

    constexpr explicit operator signed char() const
    {
        return *this;
    }

    constexpr explicit operator unsigned char() const
    {
        return *this;
    }

    constexpr explicit operator char16_t() const
    {
        return *this;
    }

    constexpr explicit operator char32_t() const
    {
        return *this;
    }

    constexpr explicit operator default_signed_short_type() const
    {
        return *this;
    }

    constexpr explicit operator default_unsigned_short_type() const
    {
        return *this;
    }

    constexpr operator default_signed_int_type() const
    {
        if (this->bytes_[2] & 0x80)
        {
            return (0xff << 24) |
                (this->bytes_[2] << 16) |
                (this->bytes_[1] << 8) |
                (this->bytes_[0] << 0);
        }
        else
        {
            return (this->bytes_[2] << 16) |
                (this->bytes_[1] << 8) |
                (this->bytes_[0] << 0);
        }
    }

    constexpr explicit operator default_unsigned_int_type() const
    {
        return *this;
    }

    constexpr explicit operator long() const
    {
        return *this;
    }

    constexpr explicit operator unsigned long() const
    {
        return *this;
    }

    constexpr explicit operator long long() const
    {
        return *this;
    }

    constexpr explicit operator unsigned long long() const
    {
        return *this;
    }

    explicit operator float() const
    {
        return static_cast<float>(*this);
    }

    explicit operator double() const
    {
        return *this;
    }

    explicit operator long double() const
    {
        return *this;
    }


	threebytes& operator+=(threebytes other)
    {
        *this = *this + other;
        return *this;
    }
	threebytes& operator-=(threebytes other)
    {
        *this = *this - other;
        return *this;
    }
	threebytes& operator*=(threebytes other)
    {
        *this = *this * other;
        return *this;
    }
	threebytes& operator/=(threebytes other)
    {
        *this = *this / other;
        return *this;
    }
    threebytes& operator%=(threebytes other)
    {
        *this = *this % other;
        return *this;
    }
    threebytes operator++(int)
    {
        *this = *this + 1;
        return *this;
    }
    threebytes operator--(int)
    {
        *this = *this - 1;
        return *this;
    }
    threebytes& operator++()
    {
        *this = *this + 1;
        return *this;
    }
    threebytes& operator--()
    {
        *this = *this - 1;
        return *this;
    }
    threebytes& operator&=(threebytes other)
    {
        *this = *this & other;
        return *this;
    }
    threebytes& operator|=(threebytes other)
    {
        *this = *this | other;
        return *this;
    }
    threebytes& operator^=(threebytes other)
    {
        *this = *this ^ other;
        return *this;
    }
    threebytes& operator<<=(default_signed_int_type amount)
    {
        *this = *this << amount;
        return *this;
    }
    threebytes& operator>>=(default_signed_int_type amount)
    {
        *this = *this >> amount;
        return *this;
    }

private:
	std::array<std::uint8_t, 3> bytes_;
};
#pragma pack(pop)

using int24_t = threebytes;


}

namespace std
{
    ostream& operator<<(ostream& ostream, const dsp::threebytes& val)
    {
        auto output = static_cast<std::int32_t>(val);
        ostream << output;
        return ostream;
    }

    template <> struct is_class<dsp::threebytes> { static constexpr bool value = false; };
    template <> struct is_signed<dsp::threebytes> { static constexpr bool value = true; };
    template <> struct is_integral<dsp::threebytes> { static constexpr bool value = true; };

    template <>
    class numeric_limits<dsp::threebytes>
    {
    public:
        static constexpr bool is_specialized = true;
        static constexpr bool is_signed = true;
        static constexpr bool is_integer = true;
        static constexpr bool is_exact = true;
        static constexpr bool has_infinity = false;
        static constexpr bool has_quiet_NaN = false;
        static constexpr bool has_signaling_NaN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_iec559 = false;
        static constexpr bool is_bounded = true;
        static constexpr bool is_modulo = false;
        static constexpr int digits = 127;
        static constexpr int digits10 = 38;
        static constexpr int max_digits10 = 0;
        static constexpr int radix = 2;
        static constexpr int min_exponent = 0;
        static constexpr int min_exponent10 = 0;
        static constexpr int max_exponent = 0;
        static constexpr int max_exponent10 = 0;
        static constexpr bool traps = numeric_limits<uint64_t>::traps;
        static constexpr bool tinyness_before = false;

        static constexpr std::int32_t(min)() { return -2048; }
        static constexpr std::int32_t lowest() { return -2048; }
        static constexpr std::int32_t(max)() { return 2047; }
        static constexpr std::int32_t epsilon() { return 0; }
        static constexpr std::int32_t round_error() { return 0; }
        static constexpr std::int32_t infinity() { return 0; }
        static constexpr std::int32_t quiet_NaN() { return 0; }
        static constexpr std::int32_t signaling_NaN() { return 0; }
        static constexpr std::int32_t denorm_min() { return 0; }
    };

    
}



#endif