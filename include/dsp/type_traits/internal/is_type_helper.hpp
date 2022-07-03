#ifndef __DSP_TYPE_TRAITS_INTERNAL_IS_TYPE_HELPER_HPP__
#define __DSP_TYPE_TRAITS_INTERNAL_IS_TYPE_HELPER_HPP__

#include <type_traits>

namespace dsp
{
    namespace type_traits
    {
        namespace internal
        {
            template <typename... _Tps>
            struct is_type_helper
            {
            };
        }

    }
}

#endif