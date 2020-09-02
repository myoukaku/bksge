/**
 *	@file	iter_rvalue_reference_t.hpp
 *
 *	@brief	iter_rvalue_reference_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_RVALUE_REFERENCE_T_HPP
#define BKSGE_FND_ITERATOR_ITER_RVALUE_REFERENCE_T_HPP

#include <bksge/fnd/iterator/concepts/detail/dereferenceable.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <BKSGE_REQUIRES_PARAM(detail::dereferenceable, I)>
using iter_rvalue_reference_t = decltype(ranges::iter_move(bksge::declval<I&>()));

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_RVALUE_REFERENCE_T_HPP
