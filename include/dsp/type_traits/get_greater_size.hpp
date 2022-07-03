#ifndef __DSP_TYPE_TRAITS_GET_GREATER_SIZE_HPP__
#define __DSP_TYPE_TRAITS_GET_GREATER_SIZE_HPP__

#include <type_traits>

namespace dsp
{
	namespace type_traits
	{
		template <typename _Tp, typename _Up>
		struct get_greater_size
		{
			using type = std::conditional_t<(sizeof(_Tp) > sizeof(_Up)), _Tp, _Up>;
		};
		template <typename _Tp, typename _Up>
		using get_greater_size_t = get_greater_size<_Tp, _Up>::type;
	}
}

#endif