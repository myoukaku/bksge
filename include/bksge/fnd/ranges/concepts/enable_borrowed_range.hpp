/**
 *	@file	enable_borrowed_range.hpp
 *
 *	@brief	enable_borrowed_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool enable_borrowed_range = false;

#define BKSGE_RANGES_ENABLE_BORROWED_RANGE(...)	\
	::bksge::ranges::enable_borrowed_range<__VA_ARGS__>

#define BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(Value, ...)	\
	template<> BKSGE_INLINE_VAR BKSGE_CONSTEXPR						\
	bool ::bksge::ranges::enable_borrowed_range<__VA_ARGS__> = Value

#else

template <typename T>
struct enable_borrowed_range
{
	BKSGE_STATIC_CONSTEXPR bool value = false;
};

#define BKSGE_RANGES_ENABLE_BORROWED_RANGE(...)	\
	::bksge::ranges::enable_borrowed_range<__VA_ARGS__>::value

#define BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(Value, ...)	\
	namespace bksge { namespace ranges {	                        \
	template <>	                                                    \
	struct enable_borrowed_range<__VA_ARGS__>	                    \
	{	                                                            \
		BKSGE_STATIC_CONSTEXPR bool value = Value;	                \
	};	                                                            \
	}}

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
