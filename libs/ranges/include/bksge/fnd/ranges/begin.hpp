/**
 *	@file	begin.hpp
 *
 *	@brief	ranges::begin の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_BEGIN_HPP
#define BKSGE_FND_RANGES_BEGIN_HPP

#include <bksge/fnd/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/ranges/detail/has_member_begin.hpp>
#include <bksge/fnd/ranges/detail/has_adl_begin.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_all_extents.hpp>
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

struct begin_fn
{
private:
	template <
		typename T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<bksge::is_array<bksge::remove_reference_t<T>>::value>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::is_array<bksge::remove_reference_t<T>>::value
#endif
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<2>, T&& t) BKSGE_NOEXCEPT
	->decltype(t + 0)
	{
		static_assert(bksge::is_lvalue_reference<T>::value, "");
		using U = bksge::remove_all_extents_t<bksge::remove_reference_t<T>>;
		static_assert(sizeof(U) != 0, "not array of incomplete type");
		return t + 0;
	}

	template <BKSGE_REQUIRES_PARAM(has_member_begin, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(t.begin()))
	->decltype(t.begin())
	{
		return t.begin();
	}

	template <BKSGE_REQUIRES_PARAM(has_adl_begin, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<0>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(begin(t)))
	->decltype(begin(t))
	{
		return begin(t);
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
detail::begin_fn begin{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_BEGIN_HPP
