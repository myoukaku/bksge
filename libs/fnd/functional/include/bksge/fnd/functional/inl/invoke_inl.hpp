/**
 *	@file	invoke_inl.hpp
 *
 *	@brief	invoke 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_INL_INVOKE_INL_HPP
#define BKSGE_FND_FUNCTIONAL_INL_INVOKE_INL_HPP

#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/detail/is_reference_wrapper.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_member_function_pointer.hpp>
#include <bksge/fnd/type_traits/is_member_object_pointer.hpp>
#include <bksge/fnd/type_traits/detail/member_object_pointer_traits.hpp>
#include <bksge/fnd/type_traits/detail/member_function_pointer_traits.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

namespace bksge
{

namespace detail
{

template <typename F>
using member_function_class_type =
	typename bksge::detail::member_function_pointer_traits<F>::class_type;

template <typename F>
using member_object_class_type =
	typename bksge::detail::member_object_pointer_traits<F>::class_type;

// BKSGE_INVOKE_RETURN
#define BKSGE_INVOKE_RETURN(...) \
    BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)	\
		-> decltype(__VA_ARGS__) \
    { return __VA_ARGS__; }

// invoke_memfun
template <bool IsBaseOf, bool IsRefWrapper>
struct invoke_memfun_impl;

template <bool IsRefWrapper>
struct invoke_memfun_impl<true, IsRefWrapper>
{
	template <typename F, typename A0, typename... Args>
	static BKSGE_CONSTEXPR auto
	invoke(F&& f, A0&& t, Args&&... args)
	BKSGE_INVOKE_RETURN((std::forward<A0>(t).*f)(std::forward<Args>(args)...))
};

template <>
struct invoke_memfun_impl<false, true>
{
	template <typename F, typename A0, typename... Args>
	static BKSGE_CONSTEXPR auto
	invoke(F&& f, A0&& t, Args&&... args)
	BKSGE_INVOKE_RETURN((t.get().*f)(std::forward<Args>(args)...))
};

template <>
struct invoke_memfun_impl<false, false>
{
	template <typename F, typename A0, typename... Args>
	static BKSGE_CONSTEXPR auto
	invoke(F&& f, A0&& t, Args&&... args)
	BKSGE_INVOKE_RETURN(((*std::forward<A0>(t)).*f)(std::forward<Args>(args)...))
};

template <typename ClassT, typename A0>
struct invoke_memfun
	: public invoke_memfun_impl<
		bksge::is_base_of<ClassT, A0>::value,
		is_reference_wrapper<A0>::value
	>
{};

// invoke_memobj
template <bool IsBaseOf, bool IsRefWrapper>
struct invoke_memobj_impl;

template <bool IsRefWrapper>
struct invoke_memobj_impl<true, IsRefWrapper>
{
	template <typename F, typename A0>
	static BKSGE_CONSTEXPR auto
	invoke(F&& f, A0&& t)
	BKSGE_INVOKE_RETURN(std::forward<A0>(t).*f)
};

template <>
struct invoke_memobj_impl<false, true>
{
	template <typename F, typename A0>
	static BKSGE_CONSTEXPR auto
	invoke(F&& f, A0&& t)
	BKSGE_INVOKE_RETURN(t.get().*f)
};

template <>
struct invoke_memobj_impl<false, false>
{
	template <typename F, typename A0>
	static BKSGE_CONSTEXPR auto
	invoke(F&& f, A0&& t)
	BKSGE_INVOKE_RETURN((*std::forward<A0>(t)).*f)
};

template <typename ClassT, typename A0>
struct invoke_memobj
	: public invoke_memobj_impl<
		bksge::is_base_of<ClassT, A0>::value,
		is_reference_wrapper<A0>::value
	>
{};

// invoke_other
struct invoke_other
{
	template <typename F, typename... Args>
	static BKSGE_CONSTEXPR auto
	invoke(F&& f, Args&&... args)
	BKSGE_INVOKE_RETURN(std::forward<F>(f)(std::forward<Args>(args)...))
};

// invoke_impl
template <bool, bool, typename F, typename... Args>
struct invoke_impl;

template <typename F, typename A0, typename... Args>
struct invoke_impl<true, false, F, A0, Args...>
	: public invoke_memfun<member_function_class_type<F>, A0>
{};

template <typename F, typename A0, typename... Args>
struct invoke_impl<false, true, F, A0, Args...>
	: public invoke_memobj<member_object_class_type<F>, A0>
{};

template <typename F, typename... Args>
struct invoke_impl<false, false, F, Args...>
	: public invoke_other
{};

// invoke
template <typename F, typename... Args>
inline BKSGE_CONSTEXPR auto
invoke(F&& f, Args&&... args)
BKSGE_INVOKE_RETURN((invoke_impl<
		bksge::is_member_function_pointer<bksge::decay_t<F>>::value,
		bksge::is_member_object_pointer<bksge::decay_t<F>>::value,
		bksge::decay_t<F>,
		bksge::decay_t<Args>...
	>::invoke(std::forward<F>(f), std::forward<Args>(args)...)))

#undef BKSGE_INVOKE_RETURN

}	// namespace detail

}	// namespace bksge

BKSGE_WARNING_POP()

#endif // BKSGE_FND_FUNCTIONAL_INL_INVOKE_INL_HPP
