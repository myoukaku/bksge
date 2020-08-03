/**
 *	@file	size.hpp
 *
 *	@brief	ranges::size の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_SIZE_HPP
#define BKSGE_FND_RANGES_SIZE_HPP

#include <bksge/fnd/ranges/detail/has_member_size.hpp>
#include <bksge/fnd/ranges/detail/has_adl_size.hpp>
#include <bksge/fnd/ranges/detail/sentinel_size.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/ranges/concepts/detail/to_unsigned.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/extent.hpp>
#include <bksge/fnd/type_traits/is_bounded_array.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/declval.hpp>
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

struct size_fn
{
private:
	template <
		typename T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::is_bounded_array<bksge::remove_reference_t<T>>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::is_bounded_array<bksge::remove_reference_t<T>>::value
#endif
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<3>, T&&) BKSGE_NOEXCEPT
	->decltype(bksge::extent<bksge::remove_reference_t<T>>::value)
	{
		return bksge::extent<bksge::remove_reference_t<T>>::value;
	}

	template <BKSGE_REQUIRE(has_member_size, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<2>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(bksge::forward<T>(t).size()))
	->decltype(bksge::forward<T>(t).size())
	{
		return bksge::forward<T>(t).size();
	}

	template <BKSGE_REQUIRE(has_adl_size, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(size(bksge::forward<T>(t))))
	->decltype(size(bksge::forward<T>(t)))
	{
		return size(bksge::forward<T>(t));
	}

	template <BKSGE_REQUIRE(sentinel_size, T)>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<0>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			to_unsigned(ranges::end(bksge::forward<T>(t)) - ranges::begin(bksge::forward<T>(t))))

public:
	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			impl(bksge::detail::overload_priority<3>{}, bksge::forward<T>(t)))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::size_fn size{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_SIZE_HPP
