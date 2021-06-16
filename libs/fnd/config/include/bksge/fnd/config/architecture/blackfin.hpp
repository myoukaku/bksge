/**
 *	@file	blackfin.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_BLACKFIN を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_ARCHITECTURE_BLACKFIN_HPP
#define BKSGE_FND_CONFIG_ARCHITECTURE_BLACKFIN_HPP

#if defined(__bfin__) || defined(__BFIN__) || \
    defined(bfin)     || defined(BFIN)
#  define BKSGE_ARCHITECTURE "blackfin"
#  define BKSGE_ARCHITECTURE_BLACKFIN
#endif

#endif // BKSGE_FND_CONFIG_ARCHITECTURE_BLACKFIN_HPP
