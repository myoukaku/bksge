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
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename... Args>
concept constructible_from =
	bksge::destructible<T> &&
	bksge::is_constructible<T, Args...>::value;

#endif

template <typename T, typename... Args>
struct constructible_from_t
	: public bksge::conjunction<
		bksge::destructible_t<T>,
		bksge::is_constructible<T, Args...>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
