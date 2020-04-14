/**
 *	@file	tuple_element.hpp
 *
 *	@brief	tuple_element の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_TUPLE_ELEMENT_HPP
#define BKSGE_FND_SPAN_TUPLE_ELEMENT_HPP

#include <bksge/fnd/span/fwd/span_fwd.hpp>
#include <bksge/fnd/span/dynamic_extent.hpp>
#include <cstddef>
#include <tuple>

namespace std
{

template <std::size_t I, typename T, std::size_t N>
struct tuple_element<I, bksge::span<T, N>>
{
	static_assert(bksge::dynamic_extent != N, "std::tuple_element<> not supported for std::span<T, dynamic_extent>");
	static_assert(I < N, "Index out of bounds in std::tuple_element<> (std::span)");
	using type = T;
};

}	// namespace std

#endif // BKSGE_FND_SPAN_TUPLE_ELEMENT_HPP
