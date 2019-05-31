/**
 *	@file	accumulate.hpp
 *
 *	@brief	accumulate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TPP_ACCUMULATE_HPP
#define BKSGE_TPP_ACCUMULATE_HPP

#include <bksge/config.hpp>

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

#include <bksge/tpp/inl/accumulate_inl.hpp>

#endif // BKSGE_TPP_ACCUMULATE_HPP
