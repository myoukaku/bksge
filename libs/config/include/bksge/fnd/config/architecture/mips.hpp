/**
 *	@file	mips.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_MIPS を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_ARCHITECTURE_MIPS_HPP
#define BKSGE_FND_CONFIG_ARCHITECTURE_MIPS_HPP

#if defined(__mips__) || defined(__mips) || \
    defined(__MIPS__)
#  define BKSGE_ARCHITECTURE "mips"
#  define BKSGE_ARCHITECTURE_MIPS
#endif

#endif // BKSGE_FND_CONFIG_ARCHITECTURE_MIPS_HPP
