/**
 *	@file	all_of.hpp
 *
 *	@brief	all_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TPP_ALL_OF_HPP
#define BKSGE_TPP_ALL_OF_HPP

#include <bksge/config.hpp>

namespace bksge
{

namespace tpp
{

/**
 *	@brief
 */
template <typename... Args>
BKSGE_CONSTEXPR bool all_of(Args&&... args);

}	// namespace tpp

}	// namespace bksge

#include <bksge/tpp/inl/all_of_inl.hpp>

#endif // BKSGE_TPP_ALL_OF_HPP
