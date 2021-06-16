/**
 *	@file	member_object_pointer_traits.hpp
 *
 *	@brief	member_object_pointer_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DETAIL_MEMBER_OBJECT_POINTER_TRAITS_HPP
#define BKSGE_FND_TYPE_TRAITS_DETAIL_MEMBER_OBJECT_POINTER_TRAITS_HPP

#include <bksge/fnd/preprocessor/empty.hpp>

namespace bksge
{

namespace detail
{

template <typename F>
struct member_object_pointer_traits;

#define BKSGE_MEMOBJPTR_TRAITS(CV_OPT)              \
template <typename R, typename T>	                \
struct member_object_pointer_traits<R T::* CV_OPT>	\
{	                                                \
	using result_type = R;	                        \
	using class_type = T;	                        \
}

BKSGE_MEMOBJPTR_TRAITS(BKSGE_PP_EMPTY());
BKSGE_MEMOBJPTR_TRAITS(const);
BKSGE_MEMOBJPTR_TRAITS(volatile);
BKSGE_MEMOBJPTR_TRAITS(const volatile);

#undef BKSGE_MEMOBJPTR_TRAITS

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DETAIL_MEMBER_OBJECT_POINTER_TRAITS_HPP
