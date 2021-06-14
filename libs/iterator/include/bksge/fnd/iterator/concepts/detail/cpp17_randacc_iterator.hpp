/**
 *	@file	cpp17_randacc_iterator.hpp
 *
 *	@brief	cpp17_randacc_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_RANDACC_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_RANDACC_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/detail/cpp17_bidi_iterator.hpp>
#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/concepts/totally_ordered.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept cpp17_randacc_iterator =
	cpp17_bidi_iterator<Iter> &&
	bksge::totally_ordered<Iter> &&
	requires(Iter it, typename bksge::incrementable_traits<Iter>::difference_type n)
	{
		{ it += n } -> bksge::same_as<Iter&>;
		{ it -= n } -> bksge::same_as<Iter&>;
		{ it +  n } -> bksge::same_as<Iter>;
		{ n +  it } -> bksge::same_as<Iter>;
		{ it -  n } -> bksge::same_as<Iter>;
		{ it - it } -> bksge::same_as<decltype(n)>;
		{  it[n]  } -> bksge::convertible_to<bksge::iter_reference_t<Iter>>;
	};

#else

namespace cpp17_randacc_iterator_detail
{

template <typename Iter>
struct cpp17_randacc_iterator_impl
{
private:
	template <typename I2,
		typename = bksge::enable_if_t<cpp17_bidi_iterator<I2>::value>,
		typename = bksge::enable_if_t<bksge::totally_ordered<I2>::value>,
		typename D = typename bksge::incrementable_traits<I2>::difference_type,
		typename T1 = decltype(bksge::declval<I2&>() += bksge::declval<D& >()),
		typename T2 = decltype(bksge::declval<I2&>() -= bksge::declval<D& >()),
		typename T3 = decltype(bksge::declval<I2&>() +  bksge::declval<D& >()),
		typename T4 = decltype(bksge::declval<D& >() +  bksge::declval<I2&>()),
		typename T5 = decltype(bksge::declval<I2&>() -  bksge::declval<D& >()),
		typename T6 = decltype(bksge::declval<I2&>() -  bksge::declval<I2&>()),
		typename T7 = decltype(bksge::declval<I2&>()[bksge::declval<D&>()])
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<T1, I2&>,
		bksge::same_as<T2, I2&>,
		bksge::same_as<T3, I2>,
		bksge::same_as<T4, I2>,
		bksge::same_as<T5, I2>,
		bksge::same_as<T6, D>,
		bksge::convertible_to<T7, bksge::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_randacc_iterator_detail

template <typename Iter>
using cpp17_randacc_iterator =
	typename cpp17_randacc_iterator_detail::cpp17_randacc_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_RANDACC_ITERATOR_HPP
