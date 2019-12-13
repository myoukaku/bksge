/**
 *	@file	siemens.hpp
 *
 *	@brief	siemens の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_SIEMENS_HPP
#define BKSGE_FND_UNITS_SIEMENS_HPP

#include <bksge/fnd/units/volt.hpp>
#include <bksge/fnd/units/ampere.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ジーメンス(コンダクタンスの単位)
template <typename T> using siemens  = decltype(ampere<T>() / volt<T>());
BKSGE_UNITS_SI_PREFIX(siemens);
// ※単数形・複数形ともsiemens

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_SIEMENS_HPP
