/**
 *	@file	invoke_result_inl.hpp
 *
 *	@brief	invoke_result の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_INVOKE_RESULT_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_INVOKE_RESULT_INL_HPP

#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

namespace bksge
{

template <typename F, typename... ArgTypes>
struct invoke_result
	: public std::invoke_result<F, ArgTypes...>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/add_rvalue_reference.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/copy_cv.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_member_object_pointer.hpp>
#include <bksge/fnd/type_traits/is_member_function_pointer.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/detail/cv_traits.hpp>
#include <bksge/fnd/type_traits/detail/is_same_or_base_of.hpp>
#include <bksge/fnd/type_traits/detail/member_object_pointer_traits.hpp>
#include <bksge/fnd/type_traits/detail/member_function_pointer_traits.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

// invoke_result_failure
struct invoke_result_failure {};

// is_mem_fn_callable
template <typename MemFn, typename Arg>
struct is_mem_fn_callable
{
	using MemFnCv = detail::member_function_cv_traits_t<bksge::remove_reference_t<MemFn>>;
	using ArgCv   = detail::cv_traits_t<bksge::remove_reference_t<Arg>>;
	BKSGE_STATIC_CONSTEXPR bool value =
		bksge::is_same<ArgCv, detail::cv_qualifier_none>::value ||
		bksge::is_same<MemFnCv, detail::cv_qualifier_cv>::value ||
		bksge::is_same<ArgCv, MemFnCv>::value;
};

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_CLANG("-Wunused-volatile-lvalue")

// is_dereferenceable
template <typename T>
struct is_dereferenceable
{
	template <typename U>
	static auto test(int) -> decltype(*std::declval<U>(), bksge::true_type());
	template <typename...>
	static auto test(...) -> bksge::false_type;

	using type = decltype(test<T>(0));
	BKSGE_STATIC_CONSTEXPR bool value = type::value;
};

BKSGE_WARNING_POP()

// invoke_result_memfun_ref
template <typename F, typename Arg0, typename... Args>
struct invoke_result_memfun_ref
{
	template <typename U, typename UArg0, typename... UArgs>
	static auto test(int) -> bksge::type_identity<decltype((std::declval<UArg0>().*std::declval<U>())(std::declval<UArgs>()...))>;
	template <typename...>
	static auto test(...) -> invoke_result_failure;

	using type =
		bksge::conditional_t<
			is_mem_fn_callable<F, Arg0>::value,
			decltype(test<F, Arg0, Args...>(0)),
			invoke_result_failure>;
};

// invoke_result_memfun_deref
template <typename F, typename Arg0, typename... Args>
struct invoke_result_memfun_deref
	: public invoke_result_memfun_ref<F, decltype(*std::declval<Arg0>()), Args...>
{};

// invoke_result_memfun
template <typename MemFn, typename Obj, typename... Args>
struct invoke_result_memfun
{
	using T = typename member_function_pointer_traits<bksge::remove_reference_t<MemFn>>::class_type;
	using ObjVal = bksge::remove_cv_t<bksge::remove_reference_t<Obj>>;
	using type =
		typename bksge::conditional<
			is_same_or_base_of<bksge::decay_t<T>, ObjVal>::value,
			invoke_result_memfun_ref<MemFn, Obj, Args...>,
			bksge::conditional_t<
				is_dereferenceable<Obj>::value,
				invoke_result_memfun_deref<MemFn, Obj, Args...>,
				bksge::type_identity<invoke_result_failure>
			>
		>::type::type;
};

// invoke_result_pmd
template <typename Ret, typename Class, typename Arg>
struct invoke_result_pmd
{
	using ArgVal = bksge::remove_pointer_t<bksge::remove_reference_t<Arg>>;
	using type =
		bksge::conditional_t<
			is_same_or_base_of<bksge::decay_t<Class>, bksge::decay_t<ArgVal>>::value,
			bksge::conditional_t<
				bksge::is_pointer<bksge::remove_reference_t<Arg>>::value || bksge::is_lvalue_reference<Arg>::value,
				bksge::add_lvalue_reference<bksge::copy_cv_t<Ret, ArgVal>>,
				bksge::add_rvalue_reference<bksge::copy_cv_t<Ret, ArgVal>>
			>,
			invoke_result_failure
		>;
};

// invoke_result_memobj
template <typename MemPtr, typename... Args>
struct invoke_result_memobj
{
	using type = invoke_result_failure;
};

template <typename MemPtr, typename Obj>
struct invoke_result_memobj<MemPtr, Obj>
{
	using Traits =
		member_object_pointer_traits<
			bksge::remove_reference_t<MemPtr>
		>;

	using type = typename invoke_result_pmd<
		typename Traits::result_type,
		typename Traits::class_type,
		Obj
	>::type;
};

// invoke_result_other
template <typename F, typename... Args>
struct invoke_result_other
{
	template <typename U, typename... UArgs>
	static auto test(int) -> bksge::type_identity<decltype(std::declval<U>()(std::declval<UArgs>()...))>;
	template <typename...>
	static auto test(...) -> invoke_result_failure;

	using type = decltype(test<F, Args...>(0));
};

// invoke_result_impl
template <bool, bool, typename F, typename... Args>
struct invoke_result_impl
{
	using type = invoke_result_failure;
};

template <typename F, typename Arg, typename... Args>
struct invoke_result_impl<true, false, F, Arg, Args...>
	: public invoke_result_memobj<F, Arg, Args...>
{};

template <typename F, typename Arg, typename... Args>
struct invoke_result_impl<false, true, F, Arg, Args...>
	: public invoke_result_memfun<F, Arg, Args...>
{};

template <typename F, typename... Args>
struct invoke_result_impl<false, false, F, Args...>
	: public invoke_result_other<F, Args...>
{};

}	// namespace detail

// invoke_result
template <typename F, typename... ArgTypes>
struct invoke_result
	: public detail::invoke_result_impl<
		bksge::is_member_object_pointer<bksge::remove_reference_t<F>>::value,
		bksge::is_member_function_pointer<bksge::remove_reference_t<F>>::value,
		F, ArgTypes...
	>::type
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_INVOKE_RESULT_INL_HPP
