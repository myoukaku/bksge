/**
 *	@file	assertion_handler.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_DEBUG_ASSERTION_HANDLER_HPP
#define BKSGE_DEBUG_ASSERTION_HANDLER_HPP

#include <bksge/debug/assertion_info.hpp>
#include <functional>	// function

namespace bksge
{

namespace debug
{

using assertion_handler = std::function<void (assertion_info const&)>;

assertion_handler const& get_assertion_handler(void);

void set_assertion_handler(assertion_handler const& handler);

}	// namespace debug

}	// namespace bksge

#include <bksge/debug/inl/assertion_handler_inl.hpp>

#endif // BKSGE_DEBUG_ASSERTION_HANDLER_HPP
