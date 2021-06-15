/**
 *	@file	kayser.hpp
 *
 *	@brief	kayser の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_KAYSER_HPP
#define BKSGE_FND_UNITS_KAYSER_HPP

#include <bksge/fnd/units/metre.hpp>

namespace bksge
{

namespace units
{

// カイザー
template <typename T> using kayser  = decltype(T() / centimetre<T>());
template <typename T> using kaysers = kayser<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_KAYSER_HPP
