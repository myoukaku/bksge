/**
 *	@file	crend.hpp
 *
 *	@brief	ranges::crend の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CREND_HPP
#define BKSGE_FND_RANGES_CREND_HPP

#include <bksge/fnd/ranges/rend.hpp>
#include <bksge/fnd/ranges/detail/as_const.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace bksge
{

namespace ranges
{

namespace detail
{

struct crend_fn
{
	template <typename T>
	constexpr auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			ranges::rend(ranges::detail::as_const(std::forward<T>(t))))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::crend_fn crend{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_CREND_HPP
