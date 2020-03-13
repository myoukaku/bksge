/**
 *	@file	overflow_error_inl.hpp
 *
 *	@brief	overflow_error の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_OVERFLOW_ERROR_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_OVERFLOW_ERROR_INL_HPP

#include <bksge/fnd/stdexcept/overflow_error.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

BKSGE_NORETURN BKSGE_INLINE
void throw_overflow_error(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::overflow_error(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_OVERFLOW_ERROR_INL_HPP
