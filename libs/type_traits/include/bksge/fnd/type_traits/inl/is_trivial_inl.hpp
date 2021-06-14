/**
 *	@file	is_trivial_inl.hpp
 *
 *	@brief	is_trivial の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIAL_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIAL_INL_HPP

#include <bksge/fnd/type_traits/is_trivial.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/type_traits/is_trivially_default_constructible.hpp>
#include <bksge/fnd/type_traits/remove_all_extents.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if (defined(BKSGE_MSVC) && (BKSGE_MSVC >= 1500)) || \
	BKSGE_HAS_FEATURE(is_trivial)

template <typename T>
struct is_trivial
	: public bksge::bool_constant<__is_trivial(T)>
{};

#else

template <typename T>
struct is_trivial
	: public bksge::bool_constant<
		bksge::is_trivially_copyable<T>::value &&
		bksge::is_trivially_default_constructible<T>::value
	>
{};

#endif

}	// namespace detail

template <typename T>
struct is_trivial
	: public detail::is_trivial<
		bksge::remove_cv_t<
			bksge::remove_all_extents_t<T>
		>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIAL_INL_HPP
