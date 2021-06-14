/**
 *	@file	disable_sized_range.hpp
 *
 *	@brief	disable_sized_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool disable_sized_range = false;

#define BKSGE_RANGES_DISABLE_SIZED_RANGE(...)	\
	::bksge::ranges::disable_sized_range<__VA_ARGS__>

#define BKSGE_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(Value, ...)		\
	BKSGE_INLINE_VAR BKSGE_CONSTEXPR								\
	bool disable_sized_range<__VA_ARGS__> = Value

#else

template <typename T>
struct disable_sized_range
{
	BKSGE_STATIC_CONSTEXPR bool value = false;
};

#define BKSGE_RANGES_DISABLE_SIZED_RANGE(...)	\
	::bksge::ranges::disable_sized_range<__VA_ARGS__>::value

#define BKSGE_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(Value, ...)		\
	struct disable_sized_range<__VA_ARGS__>							\
	{	                                                            \
		BKSGE_STATIC_CONSTEXPR bool value = Value;	                \
	}

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
