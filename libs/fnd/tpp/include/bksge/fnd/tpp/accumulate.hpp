/**
 *	@file	accumulate.hpp
 *
 *	@brief	accumulate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TPP_ACCUMULATE_HPP
#define BKSGE_FND_TPP_ACCUMULATE_HPP

#include <bksge/fnd/tpp/fold_left.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace tpp
{

/**
 *	@brief
 */
template <typename Result, typename... Args>
inline BKSGE_CONSTEXPR Result accumulate(Args&&... args)
{
	return bksge::tpp::fold_left(bksge::plus<>{}, Result{}, std::forward<Args>(args)...);
}

}	// namespace tpp

}	// namespace bksge

#endif // BKSGE_FND_TPP_ACCUMULATE_HPP
