/**
 *	@file	all_of.hpp
 *
 *	@brief	all_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TPP_ALL_OF_HPP
#define BKSGE_FND_TPP_ALL_OF_HPP

#include <bksge/fnd/tpp/fold_left.hpp>
#include <bksge/fnd/functional/logical_and.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace tpp
{

/**
 *	@brief
 */
template <typename... Args>
inline BKSGE_CONSTEXPR bool all_of(Args&&... args)
{
	return bksge::tpp::fold_left(bksge::logical_and<>{}, true, bksge::forward<Args>(args)...);
}

}	// namespace tpp

}	// namespace bksge

#endif // BKSGE_FND_TPP_ALL_OF_HPP
