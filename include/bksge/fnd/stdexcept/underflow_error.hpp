/**
 *	@file	underflow_error.hpp
 *
 *	@brief	underflow_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_UNDERFLOW_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_UNDERFLOW_ERROR_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::underflow_error;

BKSGE_NORETURN
void throw_underflow_error(char const* msg);

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/fnd/stdexcept/inl/underflow_error_inl.hpp>
#endif

#endif // BKSGE_FND_STDEXCEPT_UNDERFLOW_ERROR_HPP
