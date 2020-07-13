/**
 *	@file	disable_sized_sentinel_for.hpp
 *
 *	@brief	disable_sized_sentinel_for の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename Sent, typename Iter>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR bool disable_sized_sentinel_for = false;

#else

template <typename Sent, typename Iter>
struct disable_sized_sentinel_for
{
	BKSGE_STATIC_CONSTEXPR bool value = false;
};

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP
