/**
 *	@file	common_type_inl.hpp
 *
 *	@brief	common_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_COMMON_TYPE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_COMMON_TYPE_INL_HPP

#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/detail/common_type_fold.hpp>
#include <bksge/fnd/type_traits/detail/common_type_pack.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace detail
{

// If sizeof...(T) is two, ...
template <
	typename T1, typename T2,
	typename D1 = bksge::decay_t<T1>,
	typename D2 = bksge::decay_t<T2>
>
struct common_type_impl
{
	// If is_same_v<T1, D1> is false or is_same_v<T2, D2> is false,
	// let C denote the same type, if any, as common_type_t<D1, D2>.
	using type = bksge::common_type<D1, D2>;
};

template <typename T1, typename T2>
struct common_type_impl<T1, T2, T1, T2>
{
private:
	struct failure_type
	{};

	template <typename T, typename U>
	using cond_t = decltype(false ? bksge::declval<T>() : bksge::declval<U>());

	// Otherwise, if decay_t<decltype(false ? declval<D1>() : declval<D2>())>
	// denotes a valid type, let C denote that type.
	template <typename T, typename U>
	static auto test(int) -> bksge::type_identity<bksge::decay_t<cond_t<T, U>>>;

	// Otherwise, if COND-RES(CREF(D1), CREF(D2)) denotes a type,
	// let C denote the type decay_t<COND-RES(CREF(D1), CREF(D2))>.
	template <typename T, typename U>
	static auto test_2(int) -> bksge::type_identity<bksge::decay_t<cond_t<const T&, const U&>>>;

	template <typename, typename>
	static auto test_2(...) -> failure_type;

	template <typename T, typename U>
	static auto test(...) -> decltype(test_2<T, U>(0));

public:
	using type = decltype(test<T1, T2>(0));
};

template <typename T1, typename T2, typename... Rest>
struct common_type_fold<
	bksge::common_type<T1, T2>,
	detail::common_type_pack<Rest...>,
	bksge::void_t<typename bksge::common_type<T1, T2>::type>
>
	: public bksge::common_type<typename bksge::common_type<T1, T2>::type, Rest...>
{};

}	// namespace detail

// If sizeof...(T) is zero, there shall be no member type.
template <>
struct common_type<>
{};

// If sizeof...(T) is one, the same type, if any, as common_type_t<T0, T0>.
template <typename T0>
struct common_type<T0>
	: public common_type<T0, T0>
{};

// If sizeof...(T) is two, ...
template <typename T1, typename T2>
struct common_type<T1, T2>
	: public detail::common_type_impl<T1, T2>::type
{};

// If sizeof...(T) is greater than two, ...
template <typename T1, typename T2, typename... Rest>
struct common_type<T1, T2, Rest...>
	: public detail::common_type_fold<
		bksge::common_type<T1, T2>,
		detail::common_type_pack<Rest...>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_COMMON_TYPE_INL_HPP
