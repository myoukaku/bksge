/**
 *	@file	m68k.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_M68K を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_ARCHITECTURE_M68K_HPP
#define BKSGE_FND_CONFIG_ARCHITECTURE_M68K_HPP

#if defined(__m68k__) || defined(M68000)
#  define BKSGE_ARCHITECTURE "m68k"
#  define BKSGE_ARCHITECTURE_M68K
#endif

#endif // BKSGE_FND_CONFIG_ARCHITECTURE_M68K_HPP
