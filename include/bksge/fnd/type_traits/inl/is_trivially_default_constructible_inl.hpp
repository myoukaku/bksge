/**
 *	@file	is_trivially_default_constructible_inl.hpp
 *
 *	@brief	is_trivially_default_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_INL_HPP

#include <bksge/fnd/type_traits/is_trivially_default_constructible.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/is_function.hpp>
#include <bksge/fnd/type_traits/detail/is_array_unknown_bounds.hpp>
#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

template <typename T>
struct is_trivially_default_constructible
	: public bksge::conjunction<
		bksge::negation<detail::is_array_unknown_bounds<T>>,
		bksge::negation<bksge::is_function<T>>,
		detail::constant_wrapper<std::is_trivially_default_constructible<T>>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_INL_HPP
