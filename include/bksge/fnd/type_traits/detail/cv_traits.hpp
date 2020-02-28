/**
 *	@file	cv_traits.hpp
 *
 *	@brief	cv_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_CV_TRAITS_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_CV_TRAITS_HPP

#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_const.hpp>
#include <bksge/fnd/type_traits/is_volatile.hpp>
#include <bksge/fnd/preprocessor/empty.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

struct cv_qualifier_none {};
struct cv_qualifier_const {};
struct cv_qualifier_volatile {};
struct cv_qualifier_cv {};

template <typename T, bool, bool>
struct cv_traits_impl;

template <typename T> struct cv_traits_impl<T, true,  true>  { using type = cv_qualifier_cv; };
template <typename T> struct cv_traits_impl<T, true,  false> { using type = cv_qualifier_const; };
template <typename T> struct cv_traits_impl<T, false, true>  { using type = cv_qualifier_volatile; };
template <typename T> struct cv_traits_impl<T, false, false> { using type = cv_qualifier_none; };

template <typename T>
struct cv_traits
{
	using type =
		typename cv_traits_impl<
			T,
			bksge::is_const<T>::value,
			bksge::is_volatile<T>::value
		>::type;
};

template <typename T>
using cv_traits_t = typename cv_traits<T>::type;

template <typename T>
struct member_function_cv_traits;

template <typename T>
using member_function_cv_traits_t = typename member_function_cv_traits<T>::type;


#define BKSGE_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, EXCEPT) \
template <typename R, typename C, typename... Args>	                 \
struct member_function_cv_traits<                                    \
	R (C::* CV_OPT_1)(Args...) CV_OPT_2 EXCEPT>                      \
{	                                                                 \
	using type = T;	                                                 \
}

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

#define BKSGE_MEM_FN_CV_TRAITS_IMPL(CV_OPT_1, CV_OPT_2, T)                  \
	BKSGE_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, BKSGE_PP_EMPTY()); \
	BKSGE_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, noexcept)

#else

#define BKSGE_MEM_FN_CV_TRAITS_IMPL(CV_OPT_1, CV_OPT_2, T)                  \
	BKSGE_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, BKSGE_PP_EMPTY())

#endif

#define BKSGE_MEM_FN_CV_TRAITS(CV_OPT)	                                          \
	BKSGE_MEM_FN_CV_TRAITS_IMPL(CV_OPT, BKSGE_PP_EMPTY(), cv_qualifier_none);     \
	BKSGE_MEM_FN_CV_TRAITS_IMPL(CV_OPT, const,            cv_qualifier_const);    \
	BKSGE_MEM_FN_CV_TRAITS_IMPL(CV_OPT,       volatile,   cv_qualifier_volatile); \
	BKSGE_MEM_FN_CV_TRAITS_IMPL(CV_OPT, const volatile,   cv_qualifier_cv)


BKSGE_MEM_FN_CV_TRAITS(BKSGE_PP_EMPTY());
BKSGE_MEM_FN_CV_TRAITS(const);
BKSGE_MEM_FN_CV_TRAITS(volatile);
BKSGE_MEM_FN_CV_TRAITS(const volatile);

#undef BKSGE_MEM_FN_CV_TRAITS_IMPL_0
#undef BKSGE_MEM_FN_CV_TRAITS_IMPL
#undef BKSGE_MEM_FN_CV_TRAITS

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_CV_TRAITS_HPP
