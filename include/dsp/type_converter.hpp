#ifndef __DSP_TYPE_CONVERTER_HPP__
#define __DSP_TYPE_CONVERTER_HPP__

#include <ppi/iq/detail/convert_type/type_converter.hpp>

namespace ppi
{
	namespace iq
	{
		namespace internal
		{
			template <bool _ReverseEndian, typename _InputType, typename _OutputType>
			struct type_converter : detail::type_converter_impl<_ReverseEndian, _InputType, _OutputType> { };
		}
	}
}

#endif