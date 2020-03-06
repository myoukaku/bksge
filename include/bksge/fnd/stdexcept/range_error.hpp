/**
 *	@file	range_error.hpp
 *
 *	@brief	range_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_RANGE_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_RANGE_ERROR_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::range_error;

BKSGE_NORETURN
void throw_range_error(char const* msg);

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/fnd/stdexcept/inl/range_error_inl.hpp>
#endif

#endif // BKSGE_FND_STDEXCEPT_RANGE_ERROR_HPP
