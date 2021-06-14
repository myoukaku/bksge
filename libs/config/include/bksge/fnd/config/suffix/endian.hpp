/**
 *	@file	endian.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SUFFIX_ENDIAN_HPP
#define BKSGE_FND_CONFIG_SUFFIX_ENDIAN_HPP

#if (defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__)) || \
    (defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)) || \
     defined(__ARMEB__) || \
     defined(__THUMBEB__) || \
     defined(__AARCH64EB__) || \
     defined(_MIPSEB) || \
     defined(__MIPSEB) || \
     defined(__MIPSEB__)
#  define BKSGE_BIG_ENDIAN
#endif

#if (defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) || \
    (defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN)) || \
     defined(__ARMEL__) || \
     defined(__THUMBEL__) || \
     defined(__AARCH64EL__) || \
     defined(_MIPSEL) || \
     defined(__MIPSEL) || \
     defined(__MIPSEL__)
#  define BKSGE_LITTLE_ENDIAN
#endif

#if !defined(BKSGE_BIG_ENDIAN) && !defined(BKSGE_LITTLE_ENDIAN)
#  include <bksge/fnd/config/architecture.hpp>
#  if defined(BKSGE_ARCHITECTURE_M68K)   || \
      defined(BKSGE_ARCHITECTURE_PARISC) || \
      defined(BKSGE_ARCHITECTURE_SPARC)  || \
      defined(BKSGE_ARCHITECTURE_SYS370) || \
      defined(BKSGE_ARCHITECTURE_SYS390) || \
      defined(BKSGE_ARCHITECTURE_Z)
#    define BKSGE_BIG_ENDIAN
#  endif
#  if defined(BKSGE_ARCHITECTURE_AMD64) || \
      defined(BKSGE_ARCHITECTURE_IA64)  || \
      defined(BKSGE_ARCHITECTURE_X86)   || \
      defined(BKSGE_ARCHITECTURE_BLACKFIN)
#    define BKSGE_LITTLE_ENDIAN
#  endif
#endif

#endif // BKSGE_FND_CONFIG_SUFFIX_ENDIAN_HPP
