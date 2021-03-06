﻿/**
 *	@file	ppc.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_PPC を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_ARCHITECTURE_PPC_HPP
#define BKSGE_FND_CONFIG_ARCHITECTURE_PPC_HPP

#if defined(__powerpc)    || defined(__powerpc__)     || \
    defined(__POWERPC__)  || defined(__ppc__)         || \
    defined(_M_PPC)       || defined(_ARCH_PPC)       || \
    defined(__PPCGECKO__) || defined(__PPCBROADWAY__) || \
    defined(_XENON)
#  define BKSGE_ARCHITECTURE "ppc"
#  define BKSGE_ARCHITECTURE_PPC
#endif

#endif // BKSGE_FND_CONFIG_ARCHITECTURE_PPC_HPP
