/**
 *	@file	range_error_inl.hpp
 *
 *	@brief	range_error の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_RANGE_ERROR_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_RANGE_ERROR_INL_HPP

#include <bksge/fnd/stdexcept/range_error.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

BKSGE_NORETURN BKSGE_INLINE
void throw_range_error(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::range_error(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_RANGE_ERROR_INL_HPP
