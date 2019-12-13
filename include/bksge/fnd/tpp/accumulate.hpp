/**
 *	@file	accumulate.hpp
 *
 *	@brief	accumulate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TPP_ACCUMULATE_HPP
#define BKSGE_FND_TPP_ACCUMULATE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace tpp
{

/**
 *	@brief
 */
template <typename Result, typename... Args>
BKSGE_CONSTEXPR Result accumulate(Args&&... args);

}	// namespace tpp

}	// namespace bksge

#include <bksge/fnd/tpp/inl/accumulate_inl.hpp>

#endif // BKSGE_FND_TPP_ACCUMULATE_HPP
