﻿/**
 *	@file	index_sequence.hpp
 *
 *	@brief	index_sequence を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_INDEX_SEQUENCE_HPP
#define BKSGE_FND_UTILITY_INDEX_SEQUENCE_HPP

#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace bksge
{

using std::index_sequence;

}	// namespace bksge

#else

#include <bksge/fnd/utility/integer_sequence.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

template <bksge::size_t... I>
using index_sequence = bksge::integer_sequence<bksge::size_t, I...>;

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_INDEX_SEQUENCE_HPP
