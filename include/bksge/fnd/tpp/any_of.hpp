/**
 *	@file	any_of.hpp
 *
 *	@brief	any_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TPP_ANY_OF_HPP
#define BKSGE_FND_TPP_ANY_OF_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace tpp
{

/**
 *	@brief
 */
template <typename... Args>
BKSGE_CONSTEXPR bool any_of(Args&&... args);

}	// namespace tpp

}	// namespace bksge

#include <bksge/fnd/tpp/inl/any_of_inl.hpp>

#endif // BKSGE_FND_TPP_ANY_OF_HPP
