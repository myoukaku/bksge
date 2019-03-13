﻿/**
 *	@file	blackfin.hpp
 *
 *	@brief	BKSGE_ARCH_BLACKFIN を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_BLACKFIN_HPP
#define BKSGE_CONFIG_ARCHITECTURE_BLACKFIN_HPP

#if defined(__bfin__) || defined(__BFIN__) || \
    defined(bfin)     || defined(BFIN)
#  define BKSGE_ARCH_BLACKFIN
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_BLACKFIN_HPP
