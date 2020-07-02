/**
 *	@file	iter_reference_t.hpp
 *
 *	@brief	iter_reference_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_REFERENCE_T_HPP
#define BKSGE_FND_ITERATOR_ITER_REFERENCE_T_HPP

#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

template <typename I>	// dereferenceable
using iter_reference_t = decltype(*bksge::declval<I&>());

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_REFERENCE_T_HPP
