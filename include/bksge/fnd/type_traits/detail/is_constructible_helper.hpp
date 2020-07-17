/**
 *	@file	is_constructible_helper.hpp
 *
 *	@brief	is_constructible_helper の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_HELPER_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_HELPER_HPP

#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_abstract.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_function.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_rvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_unbounded_array.hpp>
#include <bksge/fnd/type_traits/is_volatile.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/remove_all_extents.hpp>
#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <bksge/fnd/type_traits/detail/is_same_or_base_of.hpp>
#include <bksge/fnd/type_traits/detail/cv_traits.hpp>
#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

namespace detail
{

template <typename T, typename Arg>
struct is_constructible_helper_0
{
	using T0 = bksge::remove_reference_t<T>;
	using A0 = bksge::remove_reference_t<Arg>;
	using T_cv = typename cv_traits<T0>::type;
	using A_cv = typename cv_traits<A0>::type;
	using type = bksge::bool_constant<
		bksge::is_same<T_cv, cv_qualifier_cv>::value ||
		bksge::is_same<A_cv, cv_qualifier_none>::value ||
		bksge::is_same<T_cv, A_cv>::value
	>;
};

// is_constructible_helper_reference_to_array
template <typename T, typename... Args>
struct is_constructible_helper_reference_to_array
	: public bksge::false_type
{};

template <typename T, typename Arg>
struct is_constructible_helper_reference_to_array<T, Arg>
{
	using T0 = bksge::remove_reference_t<T>;
	using A0 = bksge::remove_reference_t<Arg>;

	using type =
		bksge::conditional_t<
			bksge::is_lvalue_reference<Arg>::value && bksge::is_same<bksge::remove_cv_t<T0>, bksge::remove_cv_t<A0>>::value,
			typename is_constructible_helper_0<T, Arg>::type,
			bksge::conditional_t<
				bksge::is_same<bksge::remove_cv_t<T0>, bksge::remove_cv_t<A0>>::value,
				bksge::bool_constant<
					bksge::is_const<T0>::value &&
					!bksge::is_volatile<T0>::value &&
					!bksge::is_volatile<A0>::value>,
				bksge::false_type
			>
		>;
};

// is_constructible_helper
template <template <typename...> class F, typename T, typename... Args>
struct is_constructible_helper
	: public detail::constant_wrapper<
		bksge::conditional_t<
			bksge::is_lvalue_reference<T>::value &&
			bksge::is_array<bksge::remove_reference_t<T>>::value,
			typename is_constructible_helper_reference_to_array<T, Args...>::type,
			F<T, Args...>
		>
	>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_IS_CONSTRUCTIBLE_HELPER_HPP
