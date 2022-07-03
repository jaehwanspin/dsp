#ifndef __PPI_IQ_DETAIL_CONVERT_TYPE_HPP__
#define __PPI_IQ_DETAIL_CONVERT_TYPE_HPP__

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <mutex>
#include <functional>

#include <dsp/type_traits/is_stl_spec_iterator.hpp>
#include <dsp/detail/type_converter.hpp>

namespace dsp
{
	namespace detail
	{
		template <
			typename _InputType,
			typename _OutputType,
			bool _ReverseEndian = false>
		[[nodiscard]] constexpr inline _OutputType convert_type_impl(_InputType input) noexcept
		{
			_OutputType result = detail::type_converter<
				_ReverseEndian,
				_InputType,
				_OutputType>::convert(input);

			if constexpr (_ReverseEndian)
			{
				result = detail::reverse_endian(result);
			}

			return result;
		}

		template <
			bool _ReverseEndian = false,
			typename _ExecutionPolicyType,
			typename _InputIteratorType,
			typename _OutputIteratorType>
		constexpr inline void convert_type_impl(
			_ExecutionPolicyType &&execution_policy,
			_InputIteratorType in_begin,
			_InputIteratorType in_end,
			_OutputIteratorType out_begin) noexcept
		{
			static_assert(
				type_traits::is_stl_spec_iterator_v<_InputIteratorType> &&
					type_traits::is_stl_spec_iterator_v<_OutputIteratorType>,
				"why don't you put iterator type instances into this function");

			std::transform(execution_policy, in_begin, in_end, out_begin,
						   detail::type_converter<
							   _ReverseEndian,
							   typename _InputIteratorType::value_type,
							   typename _OutputIteratorType::value_type>::convert);
		}

		template <
			bool _ReverseEndian = false,
			typename _ExecutionPolicyType,
			typename _InputIteratorType,
			typename _OutputIteratorType,
			typename _ProgressCallbackHandlerType>
		constexpr inline void convert_type_impl(
			_ExecutionPolicyType &&execution_policy,
			_InputIteratorType in_begin,
			_InputIteratorType in_end,
			_OutputIteratorType out_begin,
			_ProgressCallbackHandlerType &&handler) noexcept
		{
			std::mutex mtx;
			const auto whole_size = std::distance(in_begin, in_end);
			std::size_t total_processed = 0;
			std::int64_t previous_progress = 0;

			std::transform(in_begin, in_end, out_begin,
						   [&](auto val) -> typename _OutputIteratorType::value_type
						   {
							   std::unique_lock lock(mtx);
							   auto output = detail::type_converter<
								   _ReverseEndian,
								   typename _InputIteratorType::value_type,
								   typename _OutputIteratorType::value_type>::convert(val);

							   total_processed++;
							   const decltype(previous_progress) current_progress =
								   (total_processed * 1000) / whole_size;

							   if (current_progress == (previous_progress + 1))
							   {
								   handler(static_cast<double>(current_progress) * 0.1);
							   }

							   previous_progress = current_progress;

							   return output;
						   });
		}

		template <
			bool _ReverseEndian = false,
			typename _InputIteratorType,
			typename _OutputIteratorType>
		constexpr inline void convert_type_impl(
			_InputIteratorType in_begin,
			_InputIteratorType in_end,
			_OutputIteratorType out_begin) noexcept
		{
			static_assert(
				type_traits::is_stl_spec_iterator_v<_InputIteratorType> &&
					type_traits::is_stl_spec_iterator_v<_OutputIteratorType>,
				"why don't you put iterator type instances into this function");

			std::transform(in_begin, in_end, out_begin,
						   detail::type_converter<
							   _ReverseEndian,
							   typename _InputIteratorType::value_type,
							   typename _OutputIteratorType::value_type>::convert);
		}

		template <
			bool _ReverseEndian = false,
			typename _InputIteratorType,
			typename _OutputIteratorType,
			typename _ProgressCallbackHandlerType>
		constexpr inline void convert_type_impl(
			_InputIteratorType in_begin,
			_InputIteratorType in_end,
			_OutputIteratorType out_begin,
			_ProgressCallbackHandlerType &&handler) noexcept
		{
			static_assert(
				type_traits::is_stl_spec_iterator_v<_InputIteratorType> &&
					type_traits::is_stl_spec_iterator_v<_OutputIteratorType>,
				"why don't you put iterator type instances into this function");

			const auto whole_size = std::distance(in_begin, in_end);
			std::size_t total_processed = 0;
			std::int64_t previous_progress = 0;

			std::transform(in_begin, in_end, out_begin,
						   [&](auto val) -> typename _OutputIteratorType::value_type
						   {
							   auto output = detail::type_converter<
								   _ReverseEndian,
								   typename _InputIteratorType::value_type,
								   typename _OutputIteratorType::value_type>::convert(val);

							   total_processed++;
							   const decltype(previous_progress) current_progress =
								   (total_processed * 1000) / whole_size;

							   if (current_progress == (previous_progress + 1))
							   {
								   handler(static_cast<double>(current_progress) * 0.1);
							   }

							   previous_progress = current_progress;

							   return output;
						   });
		}
	}

}

#endif