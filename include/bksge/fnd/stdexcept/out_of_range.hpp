/**
 *	@file	out_of_range.hpp
 *
 *	@brief	out_of_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_OUT_OF_RANGE_HPP
#define BKSGE_FND_STDEXCEPT_OUT_OF_RANGE_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::out_of_range;

BKSGE_NORETURN
void throw_out_of_range(char const* msg);

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/fnd/stdexcept/inl/out_of_range_inl.hpp>
#endif

#endif // BKSGE_FND_STDEXCEPT_OUT_OF_RANGE_HPP
