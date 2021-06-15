/**
 *	@file	logic_error.hpp
 *
 *	@brief	logic_error の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STDEXCEPT_LOGIC_ERROR_HPP
#define BKSGE_FND_STDEXCEPT_LOGIC_ERROR_HPP

#include <bksge/fnd/config.hpp>
#include <stdexcept>

namespace bksge
{

using std::logic_error;

BKSGE_NORETURN
void throw_logic_error(char const* msg);

}	// namespace bksge

#include <bksge/fnd/stdexcept/inl/logic_error_inl.hpp>

#endif // BKSGE_FND_STDEXCEPT_LOGIC_ERROR_HPP
