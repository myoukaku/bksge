/**
 *	@file	assertion_handler.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEBUG_ASSERTION_HANDLER_HPP
#define BKSGE_FND_DEBUG_ASSERTION_HANDLER_HPP

#include <bksge/fnd/debug/assertion_info.hpp>
#include <bksge/fnd/functional/function.hpp>

namespace bksge
{

namespace debug
{

using assertion_handler = bksge::function<void (assertion_info const&)>;

assertion_handler const& get_assertion_handler(void);

void set_assertion_handler(assertion_handler const& handler);

}	// namespace debug

}	// namespace bksge

#include <bksge/fnd/debug/inl/assertion_handler_inl.hpp>

#endif // BKSGE_FND_DEBUG_ASSERTION_HANDLER_HPP
