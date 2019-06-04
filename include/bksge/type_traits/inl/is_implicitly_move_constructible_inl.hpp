/**
 *	@file	is_implicitly_move_constructible_inl.hpp
 *
 *	@brief	is_implicitly_move_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_INL_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_INL_HPP
#define BKSGE_TYPE_TRAITS_INL_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_INL_HPP

#include <bksge/type_traits/is_implicitly_move_constructible.hpp>
#include <bksge/type_traits/is_implicitly_constructible.hpp>
#include <type_traits>

namespace bksge
{

template <typename T>
struct is_implicitly_move_constructible
	: public bksge::is_implicitly_constructible<
		T, typename std::add_rvalue_reference<T>::type
	>
{};

}	// namespace bksge

#endif // BKSGE_TYPE_TRAITS_INL_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_INL_HPP
