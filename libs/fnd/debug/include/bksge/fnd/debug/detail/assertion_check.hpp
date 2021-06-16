/**
 *	@file	assertion_check.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_DEBUG_DETAIL_ASSERTION_CHECK_HPP
#define BKSGE_FND_DEBUG_DETAIL_ASSERTION_CHECK_HPP

#include <bksge/fnd/debug/detail/assertion_failed.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace debug
{

namespace detail
{

template <typename Expr>
inline BKSGE_CONSTEXPR bool
assertion_check(
	bool cond,
	char const* file_name,
	int line_number,
	char const* function_name,
	char const* expr_str,
	Expr const& expr,
	char const* msg)
{
	return cond ? true :
		bksge::debug::detail::assertion_failed(
			file_name,
			line_number,
			function_name,
			expr_str,
			expr,
			msg);
}

}	// namespace detail

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_FND_DEBUG_DETAIL_ASSERTION_CHECK_HPP
