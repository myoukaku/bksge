/**
 *	@file	is_trivially_copyable_inl.hpp
 *
 *	@brief	is_trivially_copyable の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_COPYABLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_COPYABLE_INL_HPP

#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/is_volatile.hpp>
#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

template <typename T>
struct is_trivially_copyable
	: public bksge::conjunction<
		bksge::negation<bksge::is_volatile<T>>,
		detail::constant_wrapper<std::is_trivially_copyable<T>>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_COPYABLE_INL_HPP
