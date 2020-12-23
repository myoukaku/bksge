/**
 *	@file	binary_prefix.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_BINARY_PREFIX_HPP
#define BKSGE_FND_UNITS_DETAIL_BINARY_PREFIX_HPP

#include <cstdint>	// INTMAX_MAX
#include <ratio>

namespace bksge
{

namespace units
{

/**
 *	@brief	2進接頭辞
 */
using kibi = std::ratio<(1LL << 10)>;
using mebi = std::ratio<(1LL << 20)>;
using gibi = std::ratio<(1LL << 30)>;
using tebi = std::ratio<(1LL << 40)>;
using pebi = std::ratio<(1LL << 50)>;
using exbi = std::ratio<(1LL << 60)>;
#if INTMAX_MAX / (1LL << 30) >= (1LL << 40)	// INTMAX_MAX >= (1LL << 70)
using zebi = std::ratio<(1LL << 70)>;
#define BKSGE_UNITS_HAS_ZEBI
#endif
#if INTMAX_MAX / (1LL << 30) >= (1LL << 50)	// INTMAX_MAX >= (1LL << 80)
using yobi = std::ratio<(1LL << 80)>;
#define BKSGE_UNITS_HAS_YOBI
#endif

}	// namespace units

}	// namespace bksge

#define BKSGE_UNITS_BINARY_PREFIX_2(Name, Ratio) \
	template <typename T> using Ratio ## Name = decltype(Name<T>() * Ratio())

#if defined(BKSGE_UNITS_HAS_ZEBI)
#define BKSGE_UNITS_BINARY_PREFIX_ZEBI(Name)	BKSGE_UNITS_BINARY_PREFIX_2(Name, zebi)
#else
#define BKSGE_UNITS_BINARY_PREFIX_ZEBI(Name)
#endif

#if defined(BKSGE_UNITS_HAS_YOBI)
#define BKSGE_UNITS_BINARY_PREFIX_YOBI(Name)	BKSGE_UNITS_BINARY_PREFIX_2(Name, yobi)
#else
#define BKSGE_UNITS_BINARY_PREFIX_YOBI(Name)
#endif

#define BKSGE_UNITS_BINARY_PREFIX(Name)      \
	BKSGE_UNITS_BINARY_PREFIX_2(Name, kibi); \
	BKSGE_UNITS_BINARY_PREFIX_2(Name, mebi); \
	BKSGE_UNITS_BINARY_PREFIX_2(Name, gibi); \
	BKSGE_UNITS_BINARY_PREFIX_2(Name, tebi); \
	BKSGE_UNITS_BINARY_PREFIX_2(Name, pebi); \
	BKSGE_UNITS_BINARY_PREFIX_2(Name, exbi); \
	BKSGE_UNITS_BINARY_PREFIX_ZEBI(Name);	 \
	BKSGE_UNITS_BINARY_PREFIX_YOBI(Name)

#endif // BKSGE_FND_UNITS_DETAIL_BINARY_PREFIX_HPP
