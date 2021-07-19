/**
 *	@file	cbegin.hpp
 *
 *	@brief	ranges::cbegin の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CBEGIN_HPP
#define BKSGE_FND_RANGES_CBEGIN_HPP

#include <bksge/fnd/ranges/begin.hpp>
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

struct cbegin_fn
{
	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			ranges::begin(ranges::detail::as_const(std::forward<T>(t))))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::cbegin_fn cbegin{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_CBEGIN_HPP
