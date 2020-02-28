/**
 *	@file	member_function_pointer_traits.hpp
 *
 *	@brief	member_function_pointer_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_MEMBER_FUNCTION_POINTER_TRAITS_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_MEMBER_FUNCTION_POINTER_TRAITS_HPP

#include <bksge/fnd/preprocessor/empty.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace memfun_traits_detail
{

template <typename F>
struct member_function_pointer_traits_impl;

#define BKSGE_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, EXCEPT) \
template <typename R, typename T, typename... Args>	              \
struct member_function_pointer_traits_impl<                       \
	R (T::* CV_OPT_1)(Args...) CV_OPT_2 EXCEPT>                   \
{	                                                              \
	using result_type = R;	                                      \
	using class_type = T;	                                      \
}

#if defined(BKSGE_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

#define BKSGE_MEMFUNPTR_TRAITS_IMPL(CV_OPT_1, CV_OPT_2)                  \
	BKSGE_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, BKSGE_PP_EMPTY()); \
	BKSGE_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, noexcept)

#else

#define BKSGE_MEMFUNPTR_TRAITS_IMPL(CV_OPT_1, CV_OPT_2)                  \
	BKSGE_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, BKSGE_PP_EMPTY())

#endif

#define BKSGE_MEMFUNPTR_TRAITS(CV_OPT)                      \
	BKSGE_MEMFUNPTR_TRAITS_IMPL(CV_OPT, BKSGE_PP_EMPTY());	\
	BKSGE_MEMFUNPTR_TRAITS_IMPL(CV_OPT, const);	            \
	BKSGE_MEMFUNPTR_TRAITS_IMPL(CV_OPT, volatile);	        \
	BKSGE_MEMFUNPTR_TRAITS_IMPL(CV_OPT, const volatile)

BKSGE_MEMFUNPTR_TRAITS(BKSGE_PP_EMPTY());
BKSGE_MEMFUNPTR_TRAITS(const);
BKSGE_MEMFUNPTR_TRAITS(volatile);
BKSGE_MEMFUNPTR_TRAITS(const volatile);

#undef BKSGE_MEMFUNPTR_TRAITS_IMPL_0
#undef BKSGE_MEMFUNPTR_TRAITS_IMPL
#undef BKSGE_MEMFUNPTR_TRAITS

}	// namespace memfun_traits_detail

template <typename F>
struct member_function_pointer_traits
	: public memfun_traits_detail::member_function_pointer_traits_impl<F>
{};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_MEMBER_FUNCTION_POINTER_TRAITS_HPP
