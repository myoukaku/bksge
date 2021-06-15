/**
 *	@file	runtime_error.hpp
 *
 *	@brief	runtime_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_RUNTIME_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_RUNTIME_ERROR_HPP

#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::runtime_error;

BKSGE_NORETURN
void throw_runtime_error(char const* msg);

BKSGE_NORETURN
void throw_runtime_error(bksge::string const& msg);

}	// namespace bksge

#include <bksge/fnd/stdexcept/inl/runtime_error_inl.hpp>

#endif // BKSGE_FND_STDEXCEPT_RUNTIME_ERROR_HPP
