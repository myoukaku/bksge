/**
 *	@file	op_eq_lt.hpp
 *
 *	@brief	op_eq_lt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_OP_EQ_LT_HPP
#define BKSGE_FND_COMPARE_DETAIL_OP_EQ_LT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

#if 0//defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept op_eq_lt = requires(T&& t, U&& u)
{
	{ static_cast<T&&>(t) == static_cast<U&&>(u) } -> bksge::convertible_to<bool>;
	{ static_cast<T&&>(t) <  static_cast<U&&>(u) } -> bksge::convertible_to<bool>;
};

#else

template <typename T, typename U>
struct op_eq_lt_impl
{
private:
	template <typename T2, typename U2,
		typename R1 = decltype(std::declval<T2&&>() == std::declval<U2&&>()),
		typename R2 = decltype(std::declval<T2&&>() <  std::declval<U2&&>())
	>
	static auto test(int) -> bksge::conjunction<
		bksge::is_convertible_to<R1, bool>,
		bksge::is_convertible_to<R2, bool>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using op_eq_lt =
	typename op_eq_lt_impl<T, U>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_OP_EQ_LT_HPP
