﻿/**
 *	@file	logic_error_inl.hpp
 *
 *	@brief	logic_error の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_LOGIC_ERROR_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_LOGIC_ERROR_INL_HPP

#include <bksge/fnd/stdexcept/logic_error.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

BKSGE_NORETURN inline
void throw_logic_error(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::logic_error(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_LOGIC_ERROR_INL_HPP
