/**
 *	@file	cpp17_iterator.hpp
 *
 *	@brief	cpp17_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/detail/can_reference.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept cpp17_iterator =
	requires(Iter it)
	{
		{ *it } -> bksge::detail::can_reference;
		{ ++it } -> bksge::same_as<Iter&>;
		{ *it++ } -> bksge::detail::can_reference;
	} &&
	bksge::copyable<Iter>;

#else

namespace cpp17_iterator_detail
{

template <typename Iter>
struct cpp17_iterator_impl
{
private:
	template <typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::detail::can_reference<decltype( *bksge::declval<I2&>())>,
		bksge::same_as              <decltype(++bksge::declval<I2&>()), I2&>,
		bksge::detail::can_reference<decltype( *bksge::declval<I2&>()++)>,
		bksge::copyable<I2>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_iterator_detail

template <typename Iter>
using cpp17_iterator =
	typename cpp17_iterator_detail::cpp17_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CPP17_ITERATOR_HPP
