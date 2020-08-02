/**
 *	@file	iter_reference_t.hpp
 *
 *	@brief	iter_reference_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_REFERENCE_T_HPP
#define BKSGE_FND_ITERATOR_ITER_REFERENCE_T_HPP

#include <bksge/fnd/iterator/concepts/detail/dereferenceable.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	detail::dereferenceable I
#else
	typename I,
	typename = bksge::enable_if_t<detail::dereferenceable<I>::value>
#endif
>
using iter_reference_t = decltype(*bksge::declval<I&>());

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_REFERENCE_T_HPP
