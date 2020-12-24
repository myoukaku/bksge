/**
 *	@file	runtime_error_inl.hpp
 *
 *	@brief	runtime_error の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_RUNTIME_ERROR_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_RUNTIME_ERROR_INL_HPP

#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

BKSGE_NORETURN BKSGE_INLINE
void throw_runtime_error(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::runtime_error(msg);
#else
	(void)msg;
	std::abort();
#endif
}

BKSGE_NORETURN BKSGE_INLINE
void throw_runtime_error(bksge::string const& msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::runtime_error(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_RUNTIME_ERROR_INL_HPP
