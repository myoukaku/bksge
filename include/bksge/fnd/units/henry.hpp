/**
 *	@file	henry.hpp
 *
 *	@brief	henry の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_HENRY_HPP
#define BKSGE_FND_UNITS_HENRY_HPP

#include <bksge/fnd/units/volt.hpp>
#include <bksge/fnd/units/ampere.hpp>
#include <bksge/fnd/units/second.hpp>
#include <bksge/fnd/units/detail/si_prefix.hpp>

namespace bksge
{

namespace units
{

// ヘンリー(インダクタンスの単位)
template <typename T> using henry   = decltype(volt<T>() / ampere<T>() * second<T>());
template <typename T> using henries = henry<T>;
BKSGE_UNITS_SI_PREFIX(henry);
BKSGE_UNITS_SI_PREFIX(henries);

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_HENRY_HPP
