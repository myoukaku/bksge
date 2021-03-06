﻿/**
 *	@file	contiguous_range.hpp
 *
 *	@brief	contiguous_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP

#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/data.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept contiguous_range =
	ranges::random_access_range<T> &&
	bksge::contiguous_iterator<ranges::iterator_t<T>> &&
	requires(T& t)
	{
		{ ranges::data(t) } -> bksge::same_as<bksge::add_pointer_t<ranges::range_reference_t<T>>>;
	};

template <typename T>
using is_contiguous_range = bksge::bool_constant<contiguous_range<T>>;

#else

namespace detail
{

template <typename T>
struct contiguous_range_impl
{
private:
	template <
		typename U,
		typename = bksge::enable_if_t<ranges::random_access_range<U>::value>,
		typename = bksge::enable_if_t<bksge::contiguous_iterator<ranges::iterator_t<U>>::value>,
		typename P1 = decltype(ranges::data(bksge::declval<U&>())),
		typename P2 = bksge::add_pointer_t<ranges::range_reference_t<U>>
	>
	static auto test(int) -> bksge::same_as<P1, P2>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using contiguous_range = typename ranges::detail::contiguous_range_impl<T>::type;

template <typename T>
using is_contiguous_range = contiguous_range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP
