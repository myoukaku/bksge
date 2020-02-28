/**
 *	@file	is_pod_inl.hpp
 *
 *	@brief	is_pod の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_POD_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_POD_INL_HPP

#include <bksge/fnd/type_traits/is_pod.hpp>

#if (defined(_MSC_VER) && (_MSC_VER <= 1916))

#include <bksge/fnd/type_traits/bool_constant.hpp>
//#include <bksge/fnd/type_traits/is_trivially_default_constructible.hpp>
//#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
//#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
//#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/remove_all_extents.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace detail
{

template <typename T>
struct is_pod
	: public bksge::bool_constant<
		std::is_trivially_default_constructible<T>::value &&
		std::is_trivially_copy_constructible<T>::value    &&
		std::is_trivially_copy_assignable<T>::value       &&
		std::is_trivially_destructible<T>::value
	>
{};

}	// namespace detail

template <typename T>
struct is_pod
	: public detail::is_pod<
		bksge::remove_cv_t<
			bksge::remove_all_extents_t<T>
		>
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

template <typename T>
struct is_pod
	: public detail::constant_wrapper<
		std::is_pod<T>
	>
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_POD_INL_HPP
