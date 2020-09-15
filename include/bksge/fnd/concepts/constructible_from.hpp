/**
 *	@file	constructible_from.hpp
 *
 *	@brief	constructible_from の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
#define BKSGE_FND_CONCEPTS_CONSTRUCTIBLE_FROM_HPP

#include <bksge/fnd/concepts/destructible.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename... Args>
concept constructible_from =
	bksge::destructible<T> &&
	bksge::is_constructible<T, Args...>::value;

template <typename T, typename... Args>
using is_constructible_from = bksge::bool_constant<constructible_from<T, Args...>>;

#else

template <typename T, typename... Args>
using constructible_from =
	bksge::conjunction<
		bksge::destructible<T>,
		bksge::is_constructible<T, Args...>
	>;

template <typename T, typename... Args>
using is_constructible_from = constructible_from<T, Args...>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
