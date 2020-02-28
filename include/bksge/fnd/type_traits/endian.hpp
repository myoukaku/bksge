/**
 *	@file	endian.hpp
 *
 *	@brief	endian の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ENDIAN_HPP
#define BKSGE_FND_TYPE_TRAITS_ENDIAN_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

enum class endian
{
	little = 0,
	big    = 1,
#if defined(BKSGE_LITTLE_ENDIAN)
	native = little
#elif defined(BKSGE_BIG_ENDIAN)
	native = big
#else
	native = 2
#endif
};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ENDIAN_HPP
