/**
 *	@file	out_of_range_inl.hpp
 *
 *	@brief	out_of_range の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_OUT_OF_RANGE_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_OUT_OF_RANGE_INL_HPP

#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

BKSGE_NORETURN inline
void throw_out_of_range(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::out_of_range(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_OUT_OF_RANGE_INL_HPP
