/**
 *	@file	index_sequence.hpp
 *
 *	@brief	index_sequence を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UTILITY_INDEX_SEQUENCE_HPP
#define BKSGE_UTILITY_INDEX_SEQUENCE_HPP

#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace bksge
{

using std::index_sequence;

}	// namespace bksge

#else

#include <bksge/utility/integer_sequence.hpp>
#include <cstddef>

namespace bksge
{

template <std::size_t... I>
using index_sequence = bksge::integer_sequence<std::size_t, I...>;

}	// namespace bksge

#endif

#endif // BKSGE_UTILITY_INDEX_SEQUENCE_HPP
