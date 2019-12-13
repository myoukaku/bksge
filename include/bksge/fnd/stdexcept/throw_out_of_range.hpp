/**
 *	@file	throw_out_of_range.hpp
 *
 *	@brief	throw_out_of_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_THROW_OUT_OF_RANGE_HPP
#define BKSGE_FND_STDEXCEPT_THROW_OUT_OF_RANGE_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>
#include <cstdlib>		// abort

namespace bksge
{

BKSGE_NORETURN inline
void throw_out_of_range(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw std::out_of_range(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_THROW_OUT_OF_RANGE_HPP
