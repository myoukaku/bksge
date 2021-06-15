/**
 *	@file	underflow_error_inl.hpp
 *
 *	@brief	underflow_error の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_UNDERFLOW_ERROR_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_UNDERFLOW_ERROR_INL_HPP

#include <bksge/fnd/stdexcept/underflow_error.hpp>
#include <bksge/fnd/cstdlib/abort.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

BKSGE_NORETURN inline
void throw_underflow_error(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::underflow_error(msg);
#else
	(void)msg;
	bksge::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_UNDERFLOW_ERROR_INL_HPP
