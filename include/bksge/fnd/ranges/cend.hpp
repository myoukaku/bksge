/**
 *	@file	cend.hpp
 *
 *	@brief	ranges::cend の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CEND_HPP
#define BKSGE_FND_RANGES_CEND_HPP

#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/detail/as_const.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

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

struct cend_fn
{
	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			ranges::end(ranges::detail::as_const(bksge::forward<T>(t))))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::cend_fn cend{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_CEND_HPP
