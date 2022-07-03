#ifndef __DSP_DETAIL_REVERSE_ENDIAN_HPP__
#define __DSP_DETAIL_REVERSE_ENDIAN_HPP__

#include <cstdint>
#include <cstring>
#include <array>

namespace dsp
{
	namespace detail
	{
		template <typename _Tp>
		void reverse_endian(_Tp &value) noexcept
		{
			using type = _Tp;
			std::array<std::uint8_t, sizeof(type)> bytes;
			std::copy(reinterpret_cast<std::uint8_t *>(&value),
					  reinterpret_cast<std::uint8_t *>(&value) + sizeof(type), bytes.begin());
			std::reverse(bytes.begin(), bytes.end());
			std::copy(bytes.begin(), bytes.end(),
					  reinterpret_cast<std::uint8_t *>(&value));
		}

		template <typename _Tp>
		void reverse_endian(_Tp *value) noexcept
		{
			using type = _Tp;
			std::array<std::uint8_t, sizeof(type)> bytes;
			std::copy(reinterpret_cast<std::uint8_t *>(value),
					  reinterpret_cast<std::uint8_t *>(value) + sizeof(type), bytes.begin());
			std::reverse(bytes.begin(), bytes.end());
			std::copy(bytes.begin(), bytes.end(),
					  reinterpret_cast<std::uint8_t *>(value));
		}

		template <
			typename _BeginIteratorType,
			typename _EndIteratorType>
		void reverse_endian(_BeginIteratorType iter1, _EndIteratorType iter2)
		{
			std::for_each(iter1, iter2, reverse_endian);
		}

		template <
			typename _ExecutionPolicyType,
			typename _BeginIteratorType,
			typename _EndIteratorType>
		void reverse_endian(_ExecutionPolicyType &&exec_policy,
							_BeginIteratorType iter1, _EndIteratorType iter2)
		{
			std::for_each(exec_policy, iter1, iter2, reverse_endian);
		}
	}
}

#endif