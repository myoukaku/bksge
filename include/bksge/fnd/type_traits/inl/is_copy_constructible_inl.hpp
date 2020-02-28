/**
 *	@file	is_copy_constructible_inl.hpp
 *
 *	@brief	is_copy_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_COPY_CONSTRUCTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_COPY_CONSTRUCTIBLE_INL_HPP

#if 0

#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/add_const.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>

namespace bksge
{

template <typename T>
struct is_copy_constructible
	: public bksge::is_constructible<
		T, bksge::add_lvalue_reference_t<bksge::add_const_t<T>>
	>
{};

}	// namespace bksge

#endif

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

template <typename T>
struct is_copy_constructible
	: public detail::constant_wrapper<
		std::is_copy_constructible<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_COPY_CONSTRUCTIBLE_INL_HPP
