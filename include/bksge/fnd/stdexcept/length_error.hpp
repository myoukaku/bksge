/**
 *	@file	length_error.hpp
 *
 *	@brief	length_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_LENGTH_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_LENGTH_ERROR_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::length_error;

BKSGE_NORETURN
void throw_length_error(char const* msg);

}	// namespace bksge

#if defined(BKSGE_HEADER_ONLY)
#include <bksge/fnd/stdexcept/inl/length_error_inl.hpp>
#endif

#endif // BKSGE_FND_STDEXCEPT_LENGTH_ERROR_HPP
