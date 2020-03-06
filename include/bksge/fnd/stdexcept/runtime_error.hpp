﻿/**
 *	@file	runtime_error.hpp
 *
 *	@brief	runtime_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_RUNTIME_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_RUNTIME_ERROR_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>
#include <string>

namespace bksge
{

using std::runtime_error;

BKSGE_NORETURN
void throw_runtime_error(char const* msg);

BKSGE_NORETURN
void throw_runtime_error(std::string const& msg);

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/fnd/stdexcept/inl/runtime_error_inl.hpp>
#endif

#endif // BKSGE_FND_STDEXCEPT_RUNTIME_ERROR_HPP
