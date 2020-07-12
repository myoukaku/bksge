/**
 *	@file	strict_weak_order.hpp
 *
 *	@brief	strict_weak_order の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_STRICT_WEAK_ORDER_HPP
#define BKSGE_FND_CONCEPTS_STRICT_WEAK_ORDER_HPP

#include <bksge/fnd/concepts/relation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Rel, typename T, typename U>
concept strict_weak_order = bksge::relation<Rel, T, U>;

#endif

template <typename Rel, typename T, typename U>
struct strict_weak_order_t : public bksge::relation_t<Rel, T, U> {};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_STRICT_WEAK_ORDER_HPP
