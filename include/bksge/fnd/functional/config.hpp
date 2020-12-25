/**
 *	@file	config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_CONFIG_HPP
#define BKSGE_FND_FUNCTIONAL_CONFIG_HPP

//#define BKSGE_USE_STD_HASH

#if defined(BKSGE_USE_STD_HASH)
#  define BKSGE_HASH_NAMESPACE std
#else
#  define BKSGE_HASH_NAMESPACE bksge
#endif

#endif // BKSGE_FND_FUNCTIONAL_CONFIG_HPP
