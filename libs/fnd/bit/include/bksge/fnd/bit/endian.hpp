/**
 *	@file	endian.hpp
 *
 *	@brief	endian の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIT_ENDIAN_HPP
#define BKSGE_FND_BIT_ENDIAN_HPP

#include <bksge/fnd/bit/config.hpp>

#if defined(BKSGE_HAS_CXX_LIB_ENDIAN)

#include <bit>

namespace bksge
{

using std::endian;

}	// namespace bksge

#else

namespace bksge
{

enum class endian
{
#if defined(BKSGE_MSVC)

	little = 0,
	big    = 1,
#if defined(BKSGE_LITTLE_ENDIAN)
	native = little
#elif defined(BKSGE_BIG_ENDIAN)
	native = big
#else
	native = 2
#endif

#else

	little = __ORDER_LITTLE_ENDIAN__,
	big    = __ORDER_BIG_ENDIAN__,
	native = __BYTE_ORDER__

#endif
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_BIT_ENDIAN_HPP
