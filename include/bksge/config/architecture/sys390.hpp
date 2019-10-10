/**
 *	@file	sys390.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_SYS390 を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_SYS390_HPP
#define BKSGE_CONFIG_ARCHITECTURE_SYS390_HPP

#if defined(__s390__) || defined(__s390x__)
#  define BKSGE_ARCHITECTURE "sys390"
#  define BKSGE_ARCHITECTURE_SYS390
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_SYS390_HPP
