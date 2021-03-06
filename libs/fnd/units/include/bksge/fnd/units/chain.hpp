﻿/**
 *	@file	chain.hpp
 *
 *	@brief	chain の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_CHAIN_HPP
#define BKSGE_FND_UNITS_CHAIN_HPP

#include <bksge/fnd/units/foot.hpp>
#include <bksge/fnd/ratio/ratio.hpp>

namespace bksge
{

namespace units
{

// 国際チェーン = 66フィート(正確に20.1168m)
template <typename T> using chain  = decltype(foot<T>() * bksge::ratio<66>());
template <typename T> using chains = chain<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_CHAIN_HPP
