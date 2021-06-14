/**
 *	@file	invalid_argument_inl.hpp
 *
 *	@brief	invalid_argument の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_INVALID_ARGUMENT_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_INVALID_ARGUMENT_INL_HPP

#include <bksge/fnd/stdexcept/invalid_argument.hpp>
#include <bksge/fnd/cstdlib/abort.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

BKSGE_NORETURN BKSGE_INLINE
void throw_invalid_argument(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::invalid_argument(msg);
#else
	(void)msg;
	bksge::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_INVALID_ARGUMENT_INL_HPP
