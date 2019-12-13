/**
 *	@file	index_sequence_for.hpp
 *
 *	@brief	index_sequence_for を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_INDEX_SEQUENCE_FOR_HPP
#define BKSGE_FND_UTILITY_INDEX_SEQUENCE_FOR_HPP

#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace bksge
{

using std::index_sequence_for;

}	// namespace bksge

#else

#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

// Visual Studio でのコンパイラ内部エラーを避けるため、
// いったんsizeof...(Types)を受け取る必要がある
template <typename... Types>
struct index_sequence_for_impl
{
	BKSGE_STATIC_CONSTEXPR auto N = sizeof...(Types);
	using type = bksge::make_index_sequence<N>;
};

}	// namespace detail

template <typename... Types>
using index_sequence_for = typename detail::index_sequence_for_impl<Types...>::type;

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_INDEX_SEQUENCE_FOR_HPP
