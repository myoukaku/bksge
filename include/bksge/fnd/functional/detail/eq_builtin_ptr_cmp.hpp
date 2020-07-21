/**
 *	@file	eq_builtin_ptr_cmp.hpp
 *
 *	@brief	eq_builtin_ptr_cmp クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_DETAIL_EQ_BUILTIN_PTR_CMP_HPP
#define BKSGE_FND_FUNCTIONAL_DETAIL_EQ_BUILTIN_PTR_CMP_HPP

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept eq_builtin_ptr_cmp =
	requires (T&& t, U&& u) { { t == u } -> bksge::same_as<bool>; } &&
	bksge::convertible_to<T, const volatile void*> &&
	bksge::convertible_to<U, const volatile void*> &&
	(
		!requires(T&& t, U&& u)
		{
			operator==(bksge::forward<T>(t), bksge::forward<U>(u));
		} &&
		!requires(T&& t, U&& u)
		{
			bksge::forward<T>(t).operator==(bksge::forward<U>(u));
		}
	);

#endif

namespace eq_builtin_ptr_cmp_t_detail
{

template <typename T, typename U, typename = void>
struct has_operator_eq
	: public bksge::false_type {};

template <typename T, typename U>
struct has_operator_eq<T, U, bksge::void_t<decltype(operator==(bksge::declval<T>(), bksge::declval<U>()))>>
	: public bksge::true_type {};

template <typename T, typename U, typename = void>
struct has_member_eq
	: public bksge::false_type {};

template <typename T, typename U>
struct has_member_eq<T, U, bksge::void_t<decltype(bksge::declval<T>().operator==(bksge::declval<U>()))>>
	: public bksge::true_type {};

template <typename T, typename U>
struct eq_builtin_ptr_cmp_t_impl
{
private:
	template <typename T2, typename U2,
		typename = bksge::enable_if_t<
			bksge::same_as_t<decltype(bksge::declval<T2>() == bksge::declval<U2>()), bool>::value &&
			bksge::convertible_to_t<T2, const volatile void*>::value &&
			bksge::convertible_to_t<U2, const volatile void*>::value &&
			!has_operator_eq<T2, U2>::value &&
			!has_member_eq<T2, U2>::value
		>
	>
	static auto test(int) -> bksge::true_type;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace eq_builtin_ptr_cmp_t_detail

template <typename T, typename U>
using eq_builtin_ptr_cmp_t =
	typename eq_builtin_ptr_cmp_t_detail::eq_builtin_ptr_cmp_t_impl<T, U>::type;

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_DETAIL_EQ_BUILTIN_PTR_CMP_HPP
