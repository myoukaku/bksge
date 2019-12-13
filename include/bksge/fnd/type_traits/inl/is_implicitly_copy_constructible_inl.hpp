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
#include <type_traits>

namespace bksge
{

template <typename T>
struct is_implicitly_copy_constructible
	: public bksge::is_implicitly_constructible<
		T,
		typename std::add_lvalue_reference<
			typename std::add_const<T>::type
		>::type
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_INL_HPP
