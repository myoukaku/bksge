/**
 *	@file	domain_error.hpp
 *
 *	@brief	domain_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_DOMAIN_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_DOMAIN_ERROR_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::domain_error;

BKSGE_NORETURN
void throw_domain_error(char const* msg);

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/fnd/stdexcept/inl/domain_error_inl.hpp>
#endif

#endif // BKSGE_FND_STDEXCEPT_DOMAIN_ERROR_HPP
