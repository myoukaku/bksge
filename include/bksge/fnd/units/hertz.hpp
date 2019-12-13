/**
 *	@file	hertz.hpp
 *
 *	@brief	hertz の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_HERTZ_HPP
#define BKSGE_FND_UNITS_HERTZ_HPP

#include <bksge/fnd/units/detail/si_prefix.hpp>
#include <bksge/fnd/units/second.hpp>

namespace bksge
{

namespace units
{

// ヘルツ
template <typename T> using hertz = decltype(T() / second<T>());
BKSGE_UNITS_SI_PREFIX(hertz);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_HERTZ_HPP
