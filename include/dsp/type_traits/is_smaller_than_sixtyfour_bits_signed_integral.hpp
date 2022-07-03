#ifndef __DSP_TYPE_TRAITS_IS_SMALLER_THAN_SIXTYFOUR_BITS_SIGNED_INTEGRAL_HPP__
#define __DSP_TYPE_TRAITS_IS_SMALLER_THAN_SIXTYFOUR_BITS_SIGNED_INTEGRAL_HPP__

#include <type_traits>

namespace dsp
{
	struct threebytes;
	namespace type_traits
	{
		template <typename _Tp>
		struct is_smaller_than_sixtyfour_bits_signed_integral : std::bool_constant<
																	(std::is_signed_v<_Tp> &&
																	 std::is_integral_v<_Tp> &&
																	 sizeof(_Tp) < 64UL) ||
																	std::is_same_v<_Tp, threebytes>>
		{
		};
		template <typename _Tp>
		constexpr inline bool is_smaller_than_sixtyfour_bits_signed_integral_v =
			is_smaller_than_sixtyfour_bits_signed_integral<_Tp>::value;
	}
}

#endif