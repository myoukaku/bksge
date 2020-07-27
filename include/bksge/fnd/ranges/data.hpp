/**
 *	@file	data.hpp
 *
 *	@brief	ranges::data の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DATA_HPP
#define BKSGE_FND_RANGES_DATA_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/ranges/detail/has_member_data.hpp>
#include <bksge/fnd/ranges/detail/begin_data.hpp>
#include <bksge/fnd/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/memory/to_address.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
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

struct data_fn
{
private:
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		has_member_data T
#else
		typename T,
		typename = bksge::enable_if_t<has_member_data<T>::value>
#endif
	>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<1>, T&& t)
		BKSGE_NOEXCEPT_IF_EXPR(decay_copy(bksge::declval<T>().data()))
	->decltype(t.data())
	{
		return t.data();
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		begin_data T
#else
		typename T,
		typename = bksge::enable_if_t<begin_data<T>::value>
#endif
	>
	static BKSGE_CONSTEXPR auto
	impl(bksge::detail::overload_priority<0>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			bksge::to_address(ranges::begin(bksge::forward<T>(t))))

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
			impl(bksge::detail::overload_priority<1>{}, bksge::forward<T>(t)))
};

}	// namespace detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::data_fn data{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_RANGES_DATA_HPP
