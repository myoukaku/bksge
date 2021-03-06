﻿/**
 *	@file	domain_error_inl.hpp
 *
 *	@brief	domain_error の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INL_DOMAIN_ERROR_INL_HPP
#define BKSGE_FND_STDEXCEPT_INL_DOMAIN_ERROR_INL_HPP

#include <bksge/fnd/stdexcept/domain_error.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdlib>

namespace bksge
{

BKSGE_NORETURN inline
void throw_domain_error(char const* msg)
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw bksge::domain_error(msg);
#else
	(void)msg;
	std::abort();
#endif
}

}	// namespace bksge

#endif // BKSGE_FND_STDEXCEPT_INL_DOMAIN_ERROR_INL_HPP
