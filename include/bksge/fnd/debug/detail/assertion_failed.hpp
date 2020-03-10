/**
 *	@file	assertion_failed.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEBUG_DETAIL_ASSERTION_FAILED_HPP
#define BKSGE_FND_DEBUG_DETAIL_ASSERTION_FAILED_HPP

#include <bksge/fnd/debug/assertion_handler.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>

namespace bksge
{

namespace debug
{

namespace detail
{

template <typename Expr>
inline bool
assertion_failed(
	char const* file_name,
	int line_number,
	char const* function_name,
	char const* expr_str,
	Expr const& expr,
	char const* msg)
{
	bksge::stringstream ss;
	ss << expr;

	bksge::debug::get_assertion_handler()(
		assertion_info(
			file_name,
			line_number,
			function_name,
			expr_str,
			ss.str().c_str(),
			msg));

	return false;
}

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_FND_DEBUG_DETAIL_ASSERTION_FAILED_HPP
