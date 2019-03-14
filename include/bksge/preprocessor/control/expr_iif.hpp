/**
 *	@file	expr_iif.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#define BKSGE_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#
# include <bksge/preprocessor/config/config.hpp>
#
# /* BKSGE_PP_EXPR_IIF */
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
#    define BKSGE_PP_EXPR_IIF(bit, expr) BKSGE_PP_EXPR_IIF_I(bit, expr)
# else
#    define BKSGE_PP_EXPR_IIF(bit, expr) BKSGE_PP_EXPR_IIF_OO((bit, expr))
#    define BKSGE_PP_EXPR_IIF_OO(par) BKSGE_PP_EXPR_IIF_I ## par
# endif
#
# define BKSGE_PP_EXPR_IIF_I(bit, expr) BKSGE_PP_EXPR_IIF_ ## bit(expr)
#
# define BKSGE_PP_EXPR_IIF_0(expr)
# define BKSGE_PP_EXPR_IIF_1(expr) expr
#
#endif // BKSGE_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
