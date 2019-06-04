/**
 *	@file	is_implicitly_default_constructible_inl.hpp
 *
 *	@brief	is_implicitly_default_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_INL_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_INL_HPP
#define BKSGE_TYPE_TRAITS_INL_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_INL_HPP

#include <bksge/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/type_traits/is_implicitly_constructible.hpp>

namespace bksge
{

template <typename T>
struct is_implicitly_default_constructible
	: public bksge::is_implicitly_constructible<T>
{};

}	// namespace bksge

#endif // BKSGE_TYPE_TRAITS_INL_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_INL_HPP
