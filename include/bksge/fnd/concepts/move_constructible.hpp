/**
 *	@file	move_constructible.hpp
 *
 *	@brief	move_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
#define BKSGE_FND_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP

#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept move_constructible =
	bksge::constructible_from<T, T> &&
	bksge::convertible_to<T, T>;

#else

template <typename T>
using move_constructible =
	bksge::conjunction<
		bksge::constructible_from<T, T>,
		bksge::convertible_to<T, T>
	>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
