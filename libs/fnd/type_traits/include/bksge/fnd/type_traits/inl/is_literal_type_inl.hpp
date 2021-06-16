/**
 *	@file	is_literal_type_inl.hpp
 *
 *	@brief	is_literal_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_LITERAL_TYPE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_LITERAL_TYPE_INL_HPP

#include <bksge/fnd/type_traits/is_literal_type.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/type_traits/is_scalar.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/remove_all_extents.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bool =
	bksge::is_void<T>::value ||
	bksge::is_scalar<T>::value ||
	bksge::is_reference<T>::value
>
struct is_literal_type
#if (defined(BKSGE_MSVC) && (BKSGE_MSVC >= 1500)) || \
	BKSGE_HAS_FEATURE(is_literal_type)
	: public bksge::bool_constant<__is_literal_type(T)>
#elif BKSGE_HAS_FEATURE(is_literal)
	: public bksge::bool_constant<__is_literal(T)>
#else
	: public bksge::bool_constant<std::is_literal_type<T>::value>
#endif
{};

template <typename T>
struct is_literal_type<T, true>
	: public bksge::true_type
{};

}	// namespace detail

template <typename T>
struct is_literal_type
	: public detail::is_literal_type<
		bksge::remove_all_extents_t<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_LITERAL_TYPE_INL_HPP
