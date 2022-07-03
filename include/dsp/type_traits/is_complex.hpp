#ifndef __DSP_TYPE_TRAITS_IS_COMPLEX_HPP__
#define __DSP_TYPE_TRAITS_IS_COMPLEX_HPP__

#include <type_traits>

#include <dsp/type_traits/internal/is_type_helper.hpp>

namespace dsp
{
    namespace type_traits
    {

        template <typename _Tp, typename _Up = void>
        struct is_complex : std::false_type
        {
        };
        template <typename _Tp>
        struct is_complex<
            _Tp,
            std::conditional_t<
                false,
                internal::is_type_helper<
                    decltype(std::declval<_Tp>().real()),
                    decltype(std::declval<_Tp>().imag())>,
                void>> : public std::true_type
        {
        };
        template <typename _Tp, typename _Up = void>
        constexpr inline bool is_complex_v = is_complex<_Tp, _Up>::value;
    }
}

#endif