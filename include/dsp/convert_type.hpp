#ifndef __DSP_CONVERT_TYPE_HPP__
#define __DSP_CONVERT_TYPE_HPP__

#include <dsp/detail/convert_type/convert_type.hpp>

namespace dsp
{
	template <
		typename _InputType,
		typename _OutputType,
		bool _ReverseEndian = false>
	[[nodiscard]] constexpr inline _OutputType convert_type(_InputType input) noexcept
	{
		return detail::convert_type_impl<_InputType, _OutputType>(input);
	}

	template <
		bool _ReverseEndian = false,
		typename _ExecutionPolicyType,
		typename _InputIteratorType,
		typename _OutputIteratorType>
	constexpr inline void convert_type(
		_ExecutionPolicyType &&executon_policy,
		_InputIteratorType in_begin,
		_InputIteratorType in_end,
		_OutputIteratorType out_begin) noexcept
	{
		detail::convert_type_impl<
			_ReverseEndian,
			_ExecutionPolicyType,
			_InputIteratorType,
			_OutputIteratorType>(
			executon_policy,
			in_begin,
			in_end,
			out_begin);
	}

	template <
		bool _ReverseEndian = false,
		typename _ExecutionPolicyType,
		typename _InputIteratorType,
		typename _OutputIteratorType,
		typename _ProgressCallbackHandlerType>
	constexpr inline void convert_type(
		_ExecutionPolicyType &&executon_policy,
		_InputIteratorType in_begin,
		_InputIteratorType in_end,
		_OutputIteratorType out_begin,
		_ProgressCallbackHandlerType &&progress_callback_handler) noexcept
	{
		detail::convert_type_impl<
			_ReverseEndian,
			_ExecutionPolicyType,
			_InputIteratorType,
			_OutputIteratorType,
			_ProgressCallbackHandlerType>(
			executon_policy,
			in_begin,
			in_end,
			out_begin,
			std::move(progress_callback_handler));
	}

	template <
		bool _ReverseEndian = false,
		typename _InputIteratorType,
		typename _OutputIteratorType>
	constexpr inline void convert_type(
		_InputIteratorType in_begin,
		_InputIteratorType in_end,
		_OutputIteratorType out_begin) noexcept
	{
		detail::convert_type_impl<
			_ReverseEndian,
			_InputIteratorType,
			_OutputIteratorType>(
			in_begin,
			in_end,
			out_begin);
	}

	template <
		bool _ReverseEndian = false,
		typename _InputIteratorType,
		typename _OutputIteratorType,
		typename _ProgressCallbackHandlerType>
	constexpr inline void convert_type(
		_InputIteratorType in_begin,
		_InputIteratorType in_end,
		_OutputIteratorType out_begin,
		_ProgressCallbackHandlerType &&progress_callback_handler) noexcept
	{
		detail::convert_type_impl<
			_ReverseEndian,
			_InputIteratorType,
			_OutputIteratorType,
			_ProgressCallbackHandlerType>(
			in_begin,
			in_end,
			out_begin,
			std::move(progress_callback_handler));
	}
}

#endif