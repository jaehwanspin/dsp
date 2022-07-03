#ifndef __PPI_IQ_DETAIL_FOURIER_TRANSFORM_HPP__
#define __PPI_IQ_DETAIL_FOURIER_TRANSFORM_HPP__

#include <complex>
#include <algorithm>
#include <ratio>

#include <dsp/fourier_transform/fourier_transformer.hpp>

namespace dsp
{
    namespace fourier_transform
    {

        template <
            bool _Inversed = false,
            typename _InputIteratorType,
            typename _OutputIteratorType>
        constexpr inline void fast_fourier_transform_impl(
            _InputIteratorType in_begin,
            _InputIteratorType in_end,
            _OutputIteratorType out_begin)
        {
            using type = typename _OutputIteratorType::value_type;
        }

    }
}

#endif