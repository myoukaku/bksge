﻿/**
 *	@file	relation.hpp
 *
 *	@brief	relation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_RELATION_HPP
#define BKSGE_FND_CONCEPTS_RELATION_HPP

#include <bksge/fnd/concepts/predicate.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Rel, typename T, typename U>
concept relation =
	bksge::predicate<Rel, T, T> &&
	bksge::predicate<Rel, U, U> &&
	bksge::predicate<Rel, T, U> &&
	bksge::predicate<Rel, U, T>;

#else

template <typename Rel, typename T, typename U>
using relation =
	bksge::conjunction<
		bksge::predicate<Rel, T, T>,
		bksge::predicate<Rel, U, U>,
		bksge::predicate<Rel, T, U>,
		bksge::predicate<Rel, U, T>
	>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_RELATION_HPP
