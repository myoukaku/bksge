/**
 *	@file	boolean_testable.hpp
 *
 *	@brief	boolean_testable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_BOOLEAN_TESTABLE_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_BOOLEAN_TESTABLE_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept boolean_testable_impl = bksge::convertible_to<T, bool>;

template <typename T>
concept boolean_testable =
	boolean_testable_impl<T> &&
	requires(T&& t)
	{
		{ !bksge::forward<T>(t) } -> boolean_testable_impl;
	};

#else

template <typename T>
struct boolean_testable_impl
{
private:
	template <typename U,
		typename V = decltype(!bksge::declval<U&&>())
	>
	static auto test(int) -> bksge::conjunction<
		bksge::convertible_to<U, bool>,
		bksge::convertible_to<V, bool>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using boolean_testable = typename boolean_testable_impl<T>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DETAIL_BOOLEAN_TESTABLE_HPP
