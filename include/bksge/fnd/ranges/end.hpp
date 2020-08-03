/**
 *	@file	end.hpp
 *
 *	@brief	ranges::end の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_END_HPP
#define BKSGE_FND_RANGES_END_HPP

#include <bksge/fnd/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/ranges/detail/has_member_end.hpp>
#include <bksge/fnd/ranges/detail/has_adl_end.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/extent.hpp>
#include <bksge/fnd/type_traits/is_bounded_array.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
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

struct end_fn
{
private:
	template <
		typename T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<bksge::is_bounded_array<bksge::remove_reference_t<T>>::value>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::is_bounded_array<bksge::remove_reference_t<T>>::value
#endif
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<2>, T&& t) BKSGE_NOEXCEPT
	->decltype(t + 0)
	{
		static_assert(bksge::is_lvalue_reference<T>::value, "");
		return t + bksge::extent<bksge::remove_reference_t<T>>::value;
	}

	template <BKSGE_REQUIRES_PARAM(has_member_end, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(t.end()))
	->decltype(t.end())
	{
		return t.end();
	}

	template <BKSGE_REQUIRES_PARAM(has_adl_end, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<0>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(end(t)))
	->decltype(end(t))
	{
		return end(t);
	}

public:
	template <BKSGE_REQUIRES_PARAM(maybe_borrowed_range, T)>
	BKSGE_CONSTEXPR auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			impl(bksge::detail::overload_priority<2>{}, bksge::forward<T>(t)))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::end_fn end{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_END_HPP
