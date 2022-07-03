#ifndef __DSP_FOURIER_TRANSFORM_HPP__
#define __DSP_FOURIER_TRANSFORM_HPP__

#include <dsp/fourier_transform/fourier_transform.hpp>

namespace dsp
{

    template <
        bool _Inversed = false,
        typename _InputIteratorType,
        typename _OutputIteratorType>
    constexpr inline void discrete_fourier_transform(
        _InputIteratorType in_begin,
        _InputIteratorType in_end,
        _OutputIteratorType out_begin)
    {

        // detail::fast_fourier_transform_impl<
        //     _Inversed,
        //     _InputIteratorType,
        //     _OutputIteratorType>(
        //     in_begin,
        //     in_end,
        //     out_begin);
    }

    // template <
    //     bool _Inversed = false,
    //     typename _InputIteratorType,
    //     typename _OutputIteratorType>
    // constexpr inline void fast_fourier_transform(
    //     _InputIteratorType in_begin,
    //     _InputIteratorType in_end,
    //     _OutputIteratorType out_begin)
    // {

    //     // detail::fast_fourier_transform_impl<
    //     //     _Inversed,
    //     //     _InputIteratorType,
    //     //     _OutputIteratorType>(
    //     //     in_begin,
    //     //     in_end,
    //     //     out_begin);
    // }

}

#endif