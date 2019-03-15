/**
 *	@file	assertion_handler_inl.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_DEBUG_INL_ASSERTION_HANDLER_INL_HPP
#define BKSGE_DEBUG_INL_ASSERTION_HANDLER_INL_HPP

#include <bksge/debug/assertion_handler.hpp>
#include <cstdlib>	// abort
#include <iostream>

namespace bksge
{

namespace debug
{

namespace detail
{

inline void default_assertion_handler(assertion_info const& info)
{
	std::cout
		<< info.file_name << "(" << info.line_number << "): error : "
		<< info.function_name      << std::endl
		<< "Assertion failed:"     << std::endl
		<< info.expr_str           << std::endl
		<< info.evaluated_expr_str << std::endl
		<< info.msg                << std::endl;

	std::abort();
}

inline assertion_handler& assertion_handler_instance(void)
{
	static assertion_handler s_assertion_handler = default_assertion_handler;
	return s_assertion_handler;
}

}	// namespace detail

inline assertion_handler const& get_assertion_handler(void)
{
	return detail::assertion_handler_instance();
}

inline void set_assertion_handler(assertion_handler const& handler)
{
	detail::assertion_handler_instance() = handler;
}

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_DEBUG_INL_ASSERTION_HANDLER_INL_HPP
