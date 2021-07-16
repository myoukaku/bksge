/**
 *	@file	cond_res.hpp
 *
 *	@brief	cond_res の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_COND_RES_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_COND_RES_HPP

#include <bksge/fnd/type_traits/copy_cv.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

BKSGE_WARNING_PUSH();

#if defined(BKSGE_CLANG_VERSION) && (BKSGE_CLANG_VERSION >= 100000)
BKSGE_WARNING_DISABLE_CLANG("-Wdeprecated-volatile");
#endif

namespace bksge
{

namespace detail
{

#if !defined(_MSC_VER)

template <typename X, typename Y>
using cond_res = decltype(false ? std::declval<X(&)()>()() : std::declval<Y(&)()>()());

#else

BKSGE_WARNING_DISABLE_MSVC(4239);

template <typename X, typename Y, typename = void>
struct cond_res_impl_base {};

template <typename X, typename Y>
struct cond_res_impl_base<X, Y,
	bksge::void_t<decltype(false ? std::declval<X(&)()>()() : std::declval<Y(&)()>()())>>
{
	using type = bksge::remove_cv_t<
		decltype(false ? std::declval<X(&)()>()() : std::declval<Y(&)()>()())
	>;
};

template <typename X, typename Y>
struct cond_res_impl
	: cond_res_impl_base<X, Y>
{};

template <typename X, typename Y>
struct cond_res_impl<X&, Y&&>
	: cond_res_impl_base<X, Y>
{};

template <typename X, typename Y>
struct cond_res_impl<X&&, Y&>
	: cond_res_impl_base<X, Y>
{};

template <typename X, typename Y>
using cond_res = typename cond_res_impl<X, Y>::type;

#endif

}	// namespace detail

}	// namespace bksge

BKSGE_WARNING_POP();

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_COND_RES_HPP
