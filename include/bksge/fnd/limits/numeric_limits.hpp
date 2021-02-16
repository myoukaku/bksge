/**
 *	@file	numeric_limits.hpp
 *
 *	@brief	numeric_limits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_LIMITS_NUMERIC_LIMITS_HPP
#define BKSGE_FND_LIMITS_NUMERIC_LIMITS_HPP

#define BKSGE_USE_STD_NUMERIC_LIMITS

#if defined(BKSGE_USE_STD_NUMERIC_LIMITS)
#  define BKSGE_NUMERIC_LIMITS_NAMESPACE std
#else
#  define BKSGE_NUMERIC_LIMITS_NAMESPACE bksge
#endif

#if defined(BKSGE_USE_STD_NUMERIC_LIMITS)

#include <limits>

namespace bksge
{

using std::numeric_limits;

}	// namespace bksge

#else

// TODO

#endif

#endif // BKSGE_FND_LIMITS_NUMERIC_LIMITS_HPP
