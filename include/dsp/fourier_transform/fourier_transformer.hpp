#ifndef __DSP_FOURIER_TRANSFORM_FOURIER_TRANSFORMER_HPP__
#define __DSP_FOURIER_TRANSFORM_FOURIER_TRANSFORMER_HPP__

#include <cstdint>
#include <cmath>
#include <numbers>
#include <type_traits>

#include <dsp/detail/parallel_indices.hpp>
#include <dsp/type_traits/is_complex.hpp>

namespace dsp
{
	namespace fourier_transform
	{

		template <
			bool _Inversed,
			typename _InputIteratorType,
			typename _OutputIteratorType,
			typename _CondIn = _InputIteratorType,
			typename _CondOut = _OutputIteratorType>
		struct fast_fourier_transformer_impl;

		/**
		 * Cooley-Tukey FFT
		 */
		template <
			bool _Inversed,
			typename _InputIteratorType,
			typename _OutputIteratorType>
		struct fast_fourier_transformer_impl<
			_Inversed,
			_InputIteratorType,
			_OutputIteratorType,
			std::enable_if_t<
				type_traits::is_complex_v<typename _InputIteratorType::value_type>,
				_InputIteratorType>,
			std::enable_if_t<
				type_traits::is_complex_v<typename _OutputIteratorType::value_type>,
				_OutputIteratorType>>
		{
			using input_type = typename _InputIteratorType::value_type;
			using output_type = typename _OutputIteratorType::value_type;
			using input_value_type = typename _InputIteratorType::value_type::value_type;
			using output_value_type = typename _OutputIteratorType::value_type::value_type;
			static constexpr std::int32_t direction = (_Inversed ? -1 : 1);

			static constexpr inline void transform(
				_InputIteratorType _Begin,
				_InputIteratorType _End,
				_OutputIteratorType _Out) noexcept
			{
				const auto container_size = std::distance(_Begin, _End);
				std::vector<std::size_t> indices(container_size);
				// create_parallel_indices(indices.begin(), indices.end());
				auto iter = _Begin;
				std::size_t swapable_index = 0;
				std::for_each(indices.begin(), indices.end(), [&](std::size_t index)
							  {
								  std::size_t bit = container_size / 2;

								  while (swapable_index >= bit)
								  {
									  std::size_t swapable_index = 0;
									  swapable_index = swapable_index - bit;
									  bit = bit / 2;
								  }

								  swapable_index = swapable_index + bit;

								  if (index < swapable_index)
								  {
									  std::swap(iter[index], iter[swapable_index]);
								  } });
			}
		};

	}
}

#endif