#ifndef __PPI_IQ_INTERNAL_PARALLEL_INDICES_HPP__
#define __PPI_IQ_INTERNAL_PARALLEL_INDICES_HPP__

#include <cstddef>
#include <algorithm>
#include <functional>

namespace ppi
{
	namespace iq
	{
		namespace internal
		{
			namespace detail
			{
				struct index_generator
				{
					static constexpr std::size_t generate_index(std::size_t& idx, std::size_t* begin_addr)
					{
						return &idx - begin_addr;
					}
				};
			}

			template <typename _IteratorType>
			constexpr void create_parallel_indices(_IteratorType begin, _IteratorType end)
			{
				auto bound_indices_generation_func = std::bind(
					detail::index_generator::generate_index, std::placeholders::_1, & (*begin));
				std::transform(begin, end, begin, bound_indices_generation_func);
			}
		}
	}
}


#endif