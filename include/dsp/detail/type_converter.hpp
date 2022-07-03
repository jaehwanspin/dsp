#ifndef __PPI_IQ_DETAIL_TYPE_CONVERTER_HPP__
#define __PPI_IQ_DETAIL_TYPE_CONVERTER_HPP__

#include <cstddef>
#include <type_traits>

#include <dsp/detail/reverse_endian.hpp>
#include <dsp/type_traits/is_smaller_than_sixtyfour_bits_signed_integral.hpp>
#include <dsp/type_traits/get_greater_size.hpp>
#include <dsp/type_traits/get_smaller_size.hpp>
#include <dsp/type_traits/to_bits.hpp>

namespace dsp
{
	namespace internal
	{
		namespace detail
		{
			namespace internal
			{
				template <typename _IntType>
				using float_conversion_ratio =
					std::ratio<
						1,
						static_cast<std::size_t>(std::numeric_limits<_IntType>::max() + 1)>;
				template <typename _IntType, typename _FloatType>
				inline constexpr _FloatType float_conversion_constant_get =
					static_cast<_FloatType>(float_conversion_ratio<_IntType>::num) /
					static_cast<_FloatType>(float_conversion_ratio<_IntType>::den);
			}

			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType,
				typename _CondTp = _InputType,
				typename _CondUp = _OutputType>
			struct type_converter_impl;

			// same -> same
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					std::is_same_v<
						_InputType,
						_OutputType>,
					_InputType>,
				std::enable_if_t<
					std::is_same_v<
						_OutputType,
						_InputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr decltype(_ReverseEndian) does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value) noexcept
				{
					constexpr auto bits = type_traits::to_bits_v<sizeof(input_type) - sizeof(output_type)>;
					output_type result = value;

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};

			// INT -> int
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						std::is_same_v<
							type_traits::get_greater_size_t<_InputType, _OutputType>,
							_InputType> &&
						type_traits::is_smaller_than_sixtyfour_bits_signed_integral_v<_InputType>,
					_InputType>,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						std::is_same_v<
							type_traits::get_smaller_size_t<_InputType, _OutputType>,
							_OutputType> &&
						type_traits::is_smaller_than_sixtyfour_bits_signed_integral_v<_OutputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr bool does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value) noexcept
				{
					constexpr auto bits = type_traits::to_bits_v<sizeof(input_type) - sizeof(output_type)>;
					output_type result = (static_cast<output_type>(value >> bits));

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};

			// int -> INT
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						std::is_same_v<
							type_traits::get_smaller_size_t<_InputType, _OutputType>,
							_InputType> &&
						type_traits::is_smaller_than_sixtyfour_bits_signed_integral_v<_InputType>,
					_InputType>,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						std::is_same_v<
							type_traits::get_greater_size_t<_InputType, _OutputType>,
							_OutputType> &&
						type_traits::is_smaller_than_sixtyfour_bits_signed_integral_v<_OutputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr bool does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value) noexcept
				{
					constexpr auto bits = type_traits::to_bits_v<sizeof(output_type) - sizeof(input_type)>;
					output_type result = (static_cast<output_type>(value) << bits);

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};

			// int -> float
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						type_traits::is_smaller_than_sixtyfour_bits_signed_integral_v<_InputType>,
					_InputType>,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						std::is_floating_point_v<_OutputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr bool does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value)
				{
					output_type result =
						static_cast<output_type>(value) *
						internal::float_conversion_constant_get<input_type, output_type>;

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};

			// flaot -> float
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						std::is_floating_point_v<_InputType>,
					_InputType>,
				std::enable_if_t<
					!std::is_same_v<
						_InputType,
						_OutputType> &&
						std::is_floating_point_v<_OutputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr bool does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value)
				{
					output_type result = static_cast<output_type>(value);

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};

			// flaot -> int
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					std::is_floating_point_v<_InputType>,
					_InputType>,
				std::enable_if_t<
					type_traits::is_smaller_than_sixtyfour_bits_signed_integral_v<_OutputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr bool does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value)
				{
					output_type result = static_cast<output_type>(
						value * static_caste<input_type>(std::numeric_limits<output_type>::max()));

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};

			// complex -> float
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					type_traits::is_complex_v<_InputType>,
					_InputType>,
				std::enable_if_t<
					std::is_floating_point_v<_OutputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr bool does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value)
				{
					output_type result = static_cast<output_type>(
						value * static_caste<input_type>(std::numeric_limits<output_type>::max()));

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};

			// float -> complex
			template <
				bool _ReverseEndian,
				typename _InputType,
				typename _OutputType>
			struct type_converter_impl<
				_ReverseEndian,
				_InputType,
				_OutputType,
				std::enable_if_t<
					std::is_floating_point_v<_OutputType>,
					_InputType>,
				std::enable_if_t<
					type_traits::is_complex_v<_InputType>,
					_OutputType>>
			{
				using output_type = _OutputType;
				using input_type = _InputType;
				static constexpr bool does_reverse_endian = _ReverseEndian;

				constexpr static inline output_type convert(const input_type value)
				{
					output_type result = static_cast<output_type>(
						value * static_caste<input_type>(std::numeric_limits<output_type>::max()));

					if constexpr (does_reverse_endian)
					{
						dsp::detail::reverse_endian(result);
					}

					return result;
				}
			};
		}
	}
}

#endif