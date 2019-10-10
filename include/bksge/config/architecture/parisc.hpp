/**
 *	@file	parisc.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_PARISC を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_PARISC_HPP
#define BKSGE_CONFIG_ARCHITECTURE_PARISC_HPP

#if defined(__hppa__) || defined(__hppa) || defined(__HPPA__)
#  define BKSGE_ARCHITECTURE "parisc"
#  define BKSGE_ARCHITECTURE_PARISC
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_PARISC_HPP
