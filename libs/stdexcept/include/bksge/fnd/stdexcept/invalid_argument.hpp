/**
 *	@file	invalid_argument.hpp
 *
 *	@brief	invalid_argument の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_INVALID_ARGUMENT_HPP
#define BKSGE_FND_STDEXCEPT_INVALID_ARGUMENT_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::invalid_argument;

BKSGE_NORETURN
void throw_invalid_argument(char const* msg);

}	// namespace bksge

#include <bksge/fnd/stdexcept/inl/invalid_argument_inl.hpp>

#endif // BKSGE_FND_STDEXCEPT_INVALID_ARGUMENT_HPP
