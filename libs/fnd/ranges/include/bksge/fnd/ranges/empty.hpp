/**
 *	@file	empty.hpp
 *
 *	@brief	ranges::empty の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_EMPTY_HPP
#define BKSGE_FND_RANGES_EMPTY_HPP

#include <bksge/fnd/ranges/detail/has_member_empty.hpp>
#include <bksge/fnd/ranges/detail/size0_empty.hpp>
#include <bksge/fnd/ranges/detail/eq_iter_empty.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
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

struct empty_fn
{
private:
	template <BKSGE_REQUIRES_PARAM(has_member_empty, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<2>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			bool(std::forward<T>(t).empty()))

	template <BKSGE_REQUIRES_PARAM(size0_empty, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			ranges::size(std::forward<T>(t)) == 0)

	template <BKSGE_REQUIRES_PARAM(eq_iter_empty, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<0>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			bool(ranges::begin(std::forward<T>(t)) == ranges::end(std::forward<T>(t))))

public:
	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			impl(bksge::detail::overload_priority<2>{}, std::forward<T>(t)))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::empty_fn empty{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_EMPTY_HPP
