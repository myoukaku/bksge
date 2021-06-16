/**
 *	@file	becquerel.hpp
 *
 *	@brief	becquerel の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_BECQUEREL_HPP
#define BKSGE_FND_UNITS_BECQUEREL_HPP

#include <bksge/fnd/units/second.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ベクレル(放射性核種の放射能を表す単位)
template <typename T> using becquerel  = decltype(T() / second<T>());
template <typename T> using becquerels = becquerel<T>;
BKSGE_UNITS_SI_PREFIX(becquerel);
BKSGE_UNITS_SI_PREFIX(becquerels);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_BECQUEREL_HPP
