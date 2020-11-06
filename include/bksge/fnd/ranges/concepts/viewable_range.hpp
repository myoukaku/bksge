/**
 *	@file	viewable_range.hpp
 *
 *	@brief	viewable_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/borrowed_range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept viewable_range =
	ranges::range<T> &&
	(ranges::borrowed_range<T> || ranges::view<bksge::remove_cvref_t<T>>);

#else

namespace detail
{

template <typename T>
struct viewable_range_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<ranges::range<U>::value>,
		typename = bksge::enable_if_t<
			bksge::disjunction<
				ranges::borrowed_range<U>,
				ranges::view<bksge::remove_cvref_t<U>>
			>::value
		>
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using viewable_range = typename ranges::detail::viewable_range_impl<T>::type;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_VIEWABLE_RANGE_HPP
