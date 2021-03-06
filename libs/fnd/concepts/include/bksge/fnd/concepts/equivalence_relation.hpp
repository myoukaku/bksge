﻿/**
 *	@file	equivalence_relation.hpp
 *
 *	@brief	equivalence_relation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_EQUIVALENCE_RELATION_HPP
#define BKSGE_FND_CONCEPTS_EQUIVALENCE_RELATION_HPP

#include <bksge/fnd/concepts/relation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Rel, typename T, typename U>
concept equivalence_relation = bksge::relation<Rel, T, U>;

#else

template <typename Rel, typename T, typename U>
using equivalence_relation = bksge::relation<Rel, T, U>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_EQUIVALENCE_RELATION_HPP
