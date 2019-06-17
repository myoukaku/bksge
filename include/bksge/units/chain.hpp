/**
 *	@file	chain.hpp
 *
 *	@brief	chain の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_CHAIN_HPP
#define BKSGE_UNITS_CHAIN_HPP

#include <bksge/units/foot.hpp>
#include <ratio>

namespace bksge
{

namespace units
{

// 国際チェーン = 66フィート(正確に20.1168m)
template <typename T> using chain  = decltype(foot<T>() * std::ratio<66>());
template <typename T> using chains = chain<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_CHAIN_HPP
