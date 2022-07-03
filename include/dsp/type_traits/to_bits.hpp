#ifndef __DSP_TYPE_TRAITS_TO_BITS_HPP__
#define __DSP_TYPE_TRAITS_TO_BITS_HPP__

#include <cstddef>
#include <chrono>

namespace dsp
{
	namespace type_traits
	{
		template <std::size_t _Bytes>
		struct to_bits
		{
			static constexpr decltype(_Bytes) value = _Bytes * 8;
		};
		template <std::size_t _Bytes>
		inline constexpr std::size_t to_bits_v = to_bits<_Bytes>::value;
	}
}

#endif