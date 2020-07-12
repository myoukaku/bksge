/**
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

#endif

template <typename Rel, typename T, typename U>
struct relation_t
	: public bksge::conjunction<
		bksge::predicate_t<Rel, T, T>,
		bksge::predicate_t<Rel, U, U>,
		bksge::predicate_t<Rel, T, U>,
		bksge::predicate_t<Rel, U, T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_RELATION_HPP
