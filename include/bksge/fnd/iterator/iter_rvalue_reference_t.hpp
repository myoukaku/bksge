/**
 *	@file	iter_rvalue_reference_t.hpp
 *
 *	@brief	iter_rvalue_reference_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_RVALUE_REFERENCE_T_HPP
#define BKSGE_FND_ITERATOR_ITER_RVALUE_REFERENCE_T_HPP

#include <bksge/fnd/iterator/iter_move.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

template <typename I>	// dereferenceable
using iter_rvalue_reference_t = decltype(ranges::iter_move(bksge::declval<I&>()));

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_RVALUE_REFERENCE_T_HPP
