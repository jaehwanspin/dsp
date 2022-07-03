#ifndef __DSP_TYPE_TRAITS_IS_STL_SPEC_ITERATOR_HPP__
#define __DSP_TYPE_TRAITS_IS_STL_SPEC_ITERATOR_HPP__

#include <type_traits>

#include <dsp/type_traits/internal/is_type_helper.hpp>

namespace dsp
{
    namespace type_traits
    {

        template <typename _Tp, typename _Up = void>
        struct is_stl_spec_iterator : std::false_type
        {
        };
        template <typename _Tp>
        struct is_stl_spec_iterator<
            _Tp,
            std::conditional_t<
                false,
                internal::is_type_helper<
                    typename _Tp::iterator_category,
                    typename _Tp::value_type,
                    typename _Tp::difference_type,
                    typename _Tp::pointer,
                    typename _Tp::reference>,
                void>> : public std::true_type
        {
        };
        template <typename _Tp, typename _Up = void>
        constexpr inline bool is_stl_spec_iterator_v = is_stl_spec_iterator<_Tp, _Up>::value;
    }
}

#endif