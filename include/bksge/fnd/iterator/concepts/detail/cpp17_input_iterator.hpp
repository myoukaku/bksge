/**
 *	@file	cpp17_input_iterator.hpp
 *
 *	@brief	cpp17_input_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_INPUT_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_INPUT_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/detail/cpp17_iterator.hpp>
#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/iterator/indirectly_readable_traits.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/concepts/equality_comparable.hpp>
#include <bksge/fnd/concepts/signed_integral.hpp>
#include <bksge/fnd/type_traits/common_reference.hpp>
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
concept cpp17_input_iterator =
	cpp17_iterator<Iter> &&
	bksge::equality_comparable<Iter> &&
	requires(Iter it)
	{
		typename bksge::incrementable_traits<Iter>::difference_type;
		typename bksge::indirectly_readable_traits<Iter>::value_type;
		typename bksge::common_reference_t<
			bksge::iter_reference_t<Iter>&&,
			typename bksge::indirectly_readable_traits<Iter>::value_type&
		>;
		typename bksge::common_reference_t<
			decltype(*it++)&&,
			typename bksge::indirectly_readable_traits<Iter>::value_type&
		>;
		requires bksge::signed_integral<typename bksge::incrementable_traits<Iter>::difference_type>;
	};

#else

namespace cpp17_input_iterator_detail
{

template <typename Iter>
struct cpp17_input_iterator_impl
{
private:
	template <typename I2,
		typename = bksge::enable_if_t<bksge::conjunction<
			cpp17_iterator<I2>,
			bksge::equality_comparable<I2>
		>::value>,
		typename D = typename bksge::incrementable_traits<I2>::difference_type,
		typename V = typename bksge::indirectly_readable_traits<I2>::value_type,
		typename = bksge::common_reference_t<bksge::iter_reference_t<I2>&&, V&>,
		typename = bksge::common_reference_t<decltype(*bksge::declval<I2&>()++)&&, V&>,
		typename = bksge::enable_if_t<bksge::signed_integral<D>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_input_iterator_detail

template <typename Iter>
using cpp17_input_iterator =
	typename cpp17_input_iterator_detail::cpp17_input_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_INPUT_ITERATOR_HPP
