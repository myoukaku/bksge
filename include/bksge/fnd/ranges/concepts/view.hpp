/**
 *	@file	view.hpp
 *
 *	@brief	view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_VIEW_HPP
#define BKSGE_FND_RANGES_CONCEPTS_VIEW_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/enable_view.hpp>
#include <bksge/fnd/concepts/semiregular.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept view =
	ranges::range<T> &&
	bksge::semiregular<T> &&
	BKSGE_RANGES_ENABLE_VIEW(T);

template <typename T>
using is_view = bksge::bool_constant<view<T>>;

#else

namespace detail
{

template <typename T>
struct view_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<ranges::range<U>::value>,
		typename = bksge::enable_if_t<bksge::semiregular<U>::value>,
		typename = bksge::enable_if_t<BKSGE_RANGES_ENABLE_VIEW(U)>
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using view = typename ranges::detail::view_impl<T>::type;

template <typename T>
using is_view = view<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_VIEW_HPP
