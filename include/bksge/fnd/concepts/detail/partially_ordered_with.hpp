/**
 *	@file	partially_ordered_with.hpp
 *
 *	@brief	partially_ordered_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_PARTIALLY_ORDERED_WITH_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_PARTIALLY_ORDERED_WITH_HPP

#include <bksge/fnd/concepts/detail/cref.hpp>
#include <bksge/fnd/concepts/detail/boolean_testable.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept partially_ordered_with =
	requires(detail::cref<T> t, detail::cref<U> u)
	{
		{ t <  u } -> detail::boolean_testable;
		{ t >  u } -> detail::boolean_testable;
		{ t <= u } -> detail::boolean_testable;
		{ t >= u } -> detail::boolean_testable;
		{ u <  t } -> detail::boolean_testable;
		{ u >  t } -> detail::boolean_testable;
		{ u <= t } -> detail::boolean_testable;
		{ u >= t } -> detail::boolean_testable;
	};

#else

template <typename T, typename U>
struct partially_ordered_with_impl
{
private:
	template <
		typename T2, typename U2,
		typename TR = detail::cref<T2>,
		typename UR = detail::cref<U2>,
		typename B1 = decltype(bksge::declval<TR>() <  bksge::declval<UR>()),
		typename B2 = decltype(bksge::declval<TR>() >  bksge::declval<UR>()),
		typename B3 = decltype(bksge::declval<TR>() <= bksge::declval<UR>()),
		typename B4 = decltype(bksge::declval<TR>() >= bksge::declval<UR>()),
		typename B5 = decltype(bksge::declval<UR>() <  bksge::declval<TR>()),
		typename B6 = decltype(bksge::declval<UR>() >  bksge::declval<TR>()),
		typename B7 = decltype(bksge::declval<UR>() <= bksge::declval<TR>()),
		typename B8 = decltype(bksge::declval<UR>() >= bksge::declval<TR>())
	>
	static auto test(int) -> bksge::conjunction<
		boolean_testable<B1>,
		boolean_testable<B2>,
		boolean_testable<B3>,
		boolean_testable<B4>,
		boolean_testable<B5>,
		boolean_testable<B6>,
		boolean_testable<B7>,
		boolean_testable<B8>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using partially_ordered_with =
	typename partially_ordered_with_impl<T, U>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DETAIL_PARTIALLY_ORDERED_WITH_HPP
