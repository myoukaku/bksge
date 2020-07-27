/**
 *	@file	rend.hpp
 *
 *	@brief	ranges::rend の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_REND_HPP
#define BKSGE_FND_RANGES_REND_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/ranges/detail/has_member_rend.hpp>
#include <bksge/fnd/ranges/detail/has_adl_rend.hpp>
#include <bksge/fnd/ranges/detail/reversable.hpp>
#include <bksge/fnd/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <bksge/fnd/iterator/make_reverse_iterator.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
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

struct rend_fn
{
private:
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		has_member_rend T
#else
		typename T,
		typename = bksge::enable_if_t<has_member_rend<T>::value>
#endif
	>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<2>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(t.rend()))
	->decltype(t.rend())
	{
		return t.rend();
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		has_adl_rend T
#else
		typename T,
		typename = bksge::enable_if_t<has_adl_rend<T>::value>
#endif
	>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(rend(t)))
	->decltype(rend(t))
	{
		return rend(t);
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		reversable T
#else
		typename T,
		typename = bksge::enable_if_t<reversable<T>::value>
#endif
	>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<0>, T&& t)
		noexcept(
			noexcept(ranges::begin(t)) &&
			bksge::is_nothrow_copy_constructible<decltype(ranges::begin(t))>::value
		)
	->decltype(bksge::make_reverse_iterator(ranges::begin(t)))
	{
		return bksge::make_reverse_iterator(ranges::begin(t));
	}

public:
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		maybe_borrowed_range T
#else
		typename T,
		typename = bksge::enable_if_t<
			maybe_borrowed_range<T>::value
		>
#endif
	>
	BKSGE_CONSTEXPR auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			impl(bksge::detail::overload_priority<2>{}, bksge::forward<T>(t)))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::rend_fn rend{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_REND_HPP
