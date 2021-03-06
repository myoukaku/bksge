﻿/**
 *	@file	enable_view.hpp
 *
 *	@brief	enable_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_ENABLE_VIEW_HPP
#define BKSGE_FND_RANGES_CONCEPTS_ENABLE_VIEW_HPP

#include <bksge/fnd/ranges/views/view_base.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool enable_view =
	is_derived_from<T, bksge::ranges::view_base>::value;

#define BKSGE_RANGES_ENABLE_VIEW(...)	\
	::bksge::ranges::enable_view<__VA_ARGS__>

#define BKSGE_RANGES_SPECIALIZE_ENABLE_VIEW(Value, ...)		\
	BKSGE_INLINE_VAR BKSGE_CONSTEXPR						\
	bool enable_view<__VA_ARGS__> = Value

#else

template <typename T>
struct enable_view
{
	BKSGE_STATIC_CONSTEXPR bool value =
		is_derived_from<T, bksge::ranges::view_base>::value;
};

#define BKSGE_RANGES_ENABLE_VIEW(...)	\
	::bksge::ranges::enable_view<__VA_ARGS__>::value

#define BKSGE_RANGES_SPECIALIZE_ENABLE_VIEW(Value, ...)	\
	struct enable_view<__VA_ARGS__>	                    \
	{	                                                \
		BKSGE_STATIC_CONSTEXPR bool value = Value;	    \
	}

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_ENABLE_VIEW_HPP
