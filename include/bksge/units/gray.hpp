/**
 *	@file	gray.hpp
 *
 *	@brief	gray の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UNITS_GRAY_HPP
#define BKSGE_UNITS_GRAY_HPP

#include <bksge/units/joule.hpp>
#include <bksge/units/gram.hpp>
#include <bksge/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// グレイ(吸収線量の単位)
template <typename T> using gray  = decltype(joule<T>() / kilogram<T>());
template <typename T> using grays = gray<T>;
BKSGE_UNITS_SI_PREFIX(gray);
BKSGE_UNITS_SI_PREFIX(grays);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_UNITS_GRAY_HPP
