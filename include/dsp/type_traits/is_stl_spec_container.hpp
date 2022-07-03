#ifndef __DSP_TYPE_TRAITS_IS_STL_SPEC_CONTAINER_HPP__
#define __DSP_TYPE_TRAITS_IS_STL_SPEC_CONTAINER_HPP__

#include <type_traits>

#include <dsp/type_traits/internal/is_type_helper.hpp>

namespace dsp
{
    namespace type_traits
    {
        template <typename _Tp, typename _Up = void>
        struct is_stl_spec_container : std::false_type
        {
        };
        template <typename _Tp>
        struct is_stl_spec_container<
            _Tp,
            std::conditional_t<
                false,
                internal::is_type_helper<
                    typename _Tp::value_type,
                    typename _Tp::size_type,
                    typename _Tp::allocator_type,
                    typename _Tp::iterator,
                    typename _Tp::const_iterator,
                    decltype(std::declval<_Tp>().size()),
                    decltype(std::declval<_Tp>().begin()),
                    decltype(std::declval<_Tp>().end()),
                    decltype(std::declval<_Tp>().cbegin()),
                    decltype(std::declval<_Tp>().cend())>,
                void>> : public std::true_type
        {
        };
        template <typename _Tp, typename _Up = void>
        constexpr inline bool is_stl_spec_container_v = is_stl_spec_container<_Tp, _Up>::value;

    }
}

#endif