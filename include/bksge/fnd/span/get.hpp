/**
 *	@file	get.hpp
 *
 *	@brief	get の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_GET_HPP
#define BKSGE_FND_SPAN_GET_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<span>)
#include <span>
#endif

#if defined(__cpp_lib_span) && (__cpp_lib_span >= 202002)

#else

#include <bksge/fnd/span/span.hpp>
#include <bksge/fnd/span/dynamic_extent.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <tuple>

namespace std
{

template <std::size_t I, typename T, std::size_t N>
BKSGE_CONSTEXPR T&
get(bksge::span<T, N> s) BKSGE_NOEXCEPT
{
	static_assert(bksge::dynamic_extent != N,
		"std::get<> not supported for std::span<T, dynamic_extent>");

	static_assert(I < N,
		"Index out of bounds in std::get<> (std::span)");

	return s[I];
}

}	// namespace std

#endif

#endif // BKSGE_FND_SPAN_GET_HPP
