/**
 *	@file	mips.hpp
 *
 *	@brief	BKSGE_ARCH_MIPS を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_MIPS_HPP
#define BKSGE_CONFIG_ARCHITECTURE_MIPS_HPP

#if defined(__mips__) || defined(__mips) || \
    defined(__MIPS__)
#  define BKSGE_ARCH_MIPS
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_MIPS_HPP
