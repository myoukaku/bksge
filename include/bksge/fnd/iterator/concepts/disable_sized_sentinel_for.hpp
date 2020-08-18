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
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool disable_sized_sentinel_for = false;

#define BKSGE_DISABLE_SIZED_SENTINEL_FOR(...)	\
	::bksge::disable_sized_sentinel_for<__VA_ARGS__>

#define BKSGE_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(Value, ...)	\
	BKSGE_INLINE_VAR BKSGE_CONSTEXPR							\
	bool disable_sized_sentinel_for<__VA_ARGS__> = Value

#else

template <typename Sent, typename Iter>
struct disable_sized_sentinel_for
{
	BKSGE_STATIC_CONSTEXPR bool value = false;
};

#define BKSGE_DISABLE_SIZED_SENTINEL_FOR(...)	\
	::bksge::disable_sized_sentinel_for<__VA_ARGS__>::value

#define BKSGE_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(Value, ...)	\
	struct disable_sized_sentinel_for<__VA_ARGS__>	    \
	{	                                                \
		BKSGE_STATIC_CONSTEXPR bool value = Value;	    \
	}

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DISABLE_SIZED_SENTINEL_FOR_HPP
