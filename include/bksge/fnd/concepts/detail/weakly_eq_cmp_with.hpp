/**
 *	@file	weakly_eq_cmp_with.hpp
 *
 *	@brief	weakly_eq_cmp_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_WEAKLY_EQ_CMP_WITH_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_WEAKLY_EQ_CMP_WITH_HPP

#include <bksge/fnd/concepts/detail/cref.hpp>
#include <bksge/fnd/concepts/detail/boolean_testable.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept weakly_eq_cmp_with =
	requires(detail::cref<T> t, detail::cref<U> u)
	{
		{ t == u } -> detail::boolean_testable;
		{ t != u } -> detail::boolean_testable;
		{ u == t } -> detail::boolean_testable;
		{ u != t } -> detail::boolean_testable;
	};

#endif

template <typename T, typename U>
struct weakly_eq_cmp_with_t_impl
{
private:
	template <
		typename T2, typename U2,
		typename TR = detail::cref<T2>,
		typename UR = detail::cref<U2>
	>
	static auto test(int) -> bksge::conjunction<
		boolean_testable_t<decltype(bksge::declval<TR>() == bksge::declval<UR>())>,
		boolean_testable_t<decltype(bksge::declval<TR>() != bksge::declval<UR>())>,
		boolean_testable_t<decltype(bksge::declval<UR>() == bksge::declval<TR>())>,
		boolean_testable_t<decltype(bksge::declval<UR>() != bksge::declval<TR>())>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
struct weakly_eq_cmp_with_t
	: public weakly_eq_cmp_with_t_impl<T, U>::type
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DETAIL_WEAKLY_EQ_CMP_WITH_HPP
