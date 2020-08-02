﻿/**
 *	@file	cpp17_fwd_iterator.hpp
 *
 *	@brief	cpp17_fwd_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_FWD_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_FWD_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/detail/cpp17_input_iterator.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/indirectly_readable_traits.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept cpp17_fwd_iterator =
	cpp17_input_iterator<Iter> &&
	bksge::constructible_from<Iter> &&
	bksge::is_lvalue_reference<bksge::iter_reference_t<Iter>>::value &&
	bksge::same_as<
		bksge::remove_cvref_t<bksge::iter_reference_t<Iter>>,
		typename bksge::indirectly_readable_traits<Iter>::value_type
	> &&
	requires(Iter it)
	{
		{  it++ } -> bksge::convertible_to<Iter const&>;
		{ *it++ } -> bksge::same_as<bksge::iter_reference_t<Iter>>;
	};

#else

namespace cpp17_fwd_iterator_detail
{

template <typename Iter>
struct cpp17_fwd_iterator_impl
{
private:
	template <typename I2>
	static auto test(int) -> bksge::conjunction<
		cpp17_input_iterator<I2>,
		bksge::constructible_from_t<I2>,
		bksge::is_lvalue_reference<bksge::iter_reference_t<I2>>,
		bksge::same_as_t<
			bksge::remove_cvref_t<bksge::iter_reference_t<I2>>,
			typename bksge::indirectly_readable_traits<I2>::value_type
		>,
		bksge::convertible_to_t<decltype( bksge::declval<I2&>()++), I2 const&>,
		bksge::same_as_t       <decltype(*bksge::declval<I2&>()++), bksge::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_fwd_iterator_detail

template <typename Iter>
using cpp17_fwd_iterator =
	typename cpp17_fwd_iterator_detail::cpp17_fwd_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_FWD_ITERATOR_HPP
