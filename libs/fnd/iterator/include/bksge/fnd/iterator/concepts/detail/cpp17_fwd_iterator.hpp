/**
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
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

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
	template <typename I2,
		typename = bksge::enable_if_t<cpp17_input_iterator<I2>::value>,
		typename = bksge::enable_if_t<bksge::constructible_from<I2>::value>,
		typename R = bksge::iter_reference_t<I2>,
		typename = bksge::enable_if_t<bksge::is_lvalue_reference<R>::value>,
		typename = bksge::enable_if_t<bksge::same_as<
			bksge::remove_cvref_t<R>,
			typename bksge::indirectly_readable_traits<I2>::value_type
		>::value>,
		typename T1 = decltype( std::declval<I2&>()++),
		typename T2 = decltype(*std::declval<I2&>()++)
	>
	static auto test(int) -> bksge::conjunction<
		bksge::convertible_to<T1, I2 const&>,
		bksge::same_as<T2, R>
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
