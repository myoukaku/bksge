/**
 *	@file	overflow_error.hpp
 *
 *	@brief	overflow_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_OVERFLOW_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_OVERFLOW_ERROR_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::overflow_error;

BKSGE_NORETURN
void throw_overflow_error(char const* msg);

}	// namespace bksge

#include <bksge/fnd/stdexcept/inl/overflow_error_inl.hpp>

#endif // BKSGE_FND_STDEXCEPT_OVERFLOW_ERROR_HPP
