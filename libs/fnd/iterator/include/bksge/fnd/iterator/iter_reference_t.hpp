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
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <BKSGE_REQUIRES_PARAM(detail::dereferenceable, I)>
using iter_reference_t = decltype(*std::declval<I&>());

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_REFERENCE_T_HPP
