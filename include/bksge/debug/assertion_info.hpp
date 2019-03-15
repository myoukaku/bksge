/**
 *	@file	assertion_info.hpp
 *
 *	@brief	assertion_infoの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_DEBUG_ASSERTION_INFO_HPP
#define BKSGE_DEBUG_ASSERTION_INFO_HPP

namespace bksge
{

namespace debug
{

struct assertion_info
{
	char const* file_name;
	int			line_number;
	char const* function_name;
	char const* expr_str;
	char const* evaluated_expr_str;
	char const* msg;

	assertion_info(
		char const* file_name_,
		int			line_number_,
		char const* function_name_,
		char const* expr_str_,
		char const* evaluated_expr_str_,
		char const* msg_)
		: file_name(file_name_)
		, line_number(line_number_)
		, function_name(function_name_)
		, expr_str(expr_str_)
		, evaluated_expr_str(evaluated_expr_str_)
		, msg(msg_)
	{}
};

}	// namespace debug

}	// namespace bksge

#endif // BKSGE_DEBUG_ASSERTION_INFO_HPP
