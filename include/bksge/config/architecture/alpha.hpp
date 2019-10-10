/**
 *	@file	alpha.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_ALPHA を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_ALPHA_HPP
#define BKSGE_CONFIG_ARCHITECTURE_ALPHA_HPP

#if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#  define BKSGE_ARCHITECTURE "alpha"
#  define BKSGE_ARCHITECTURE_ALPHA
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_ALPHA_HPP
