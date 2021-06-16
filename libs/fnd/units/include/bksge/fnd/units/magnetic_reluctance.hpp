/**
 *	@file	magnetic_reluctance.hpp
 *
 *	@brief	magnetic_reluctance の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_MAGNETIC_RELUCTANCE_HPP
#define BKSGE_FND_UNITS_MAGNETIC_RELUCTANCE_HPP

#include <bksge/fnd/units/ampere.hpp>
#include <bksge/fnd/units/weber.hpp>
#include <bksge/fnd/units/henry.hpp>

namespace bksge
{

namespace units
{

// アンペア毎ウェーバ(磁気抵抗の単位)
template <typename T> using ampere_per_weber  = decltype(ampere<T>() / weber<T>());
template <typename T> using amperes_per_weber = ampere_per_weber<T>;

// 毎ヘンリー(磁気抵抗の単位)
template <typename T> using reciprocal_henry   = decltype(T() / henry<T>());
template <typename T> using reciprocal_henries = reciprocal_henry<T>;

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_MAGNETIC_RELUCTANCE_HPP
