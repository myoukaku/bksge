/**
 *	@file	is_implicitly_copy_constructible_inl.hpp
 *
 *	@brief	is_implicitly_copy_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_INL_HPP

#include <bksge/fnd/type_traits/is_implicitly_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/add_const.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>

namespace bksge
{

template <typename T>
struct is_implicitly_copy_constructible
	: public bksge::is_implicitly_constructible<
		T, bksge::add_lvalue_reference_t<bksge::add_const_t<T>>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_INL_HPP
