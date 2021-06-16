/**
 *	@file	make_index_sequence.hpp
 *
 *	@brief	make_index_sequence を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_MAKE_INDEX_SEQUENCE_HPP
#define BKSGE_FND_UTILITY_MAKE_INDEX_SEQUENCE_HPP

#include <bksge/fnd/utility/index_sequence.hpp>
#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace bksge
{

using std::make_index_sequence;

}	// namespace bksge

#else

#include <bksge/fnd/utility/make_integer_sequence.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

template <bksge::size_t N>
using make_index_sequence = bksge::make_integer_sequence<bksge::size_t, N>;

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_MAKE_INDEX_SEQUENCE_HPP
