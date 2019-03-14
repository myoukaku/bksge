/**
 *	@file	if.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_CONTROL_IF_HPP
#define BKSGE_PREPROCESSOR_CONTROL_IF_HPP
#
# include <bksge/preprocessor/config/config.hpp>
# include <bksge/preprocessor/control/iif.hpp>
# include <bksge/preprocessor/logical/bool.hpp>
#
# /* BKSGE_PP_IF */
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_EDG()
#    define BKSGE_PP_IF(cond, t, f) BKSGE_PP_IIF(BKSGE_PP_BOOL(cond), t, f)
# else
#    define BKSGE_PP_IF(cond, t, f) BKSGE_PP_IF_I(cond, t, f)
#    define BKSGE_PP_IF_I(cond, t, f) BKSGE_PP_IIF(BKSGE_PP_BOOL(cond), t, f)
# endif
#
#endif // BKSGE_PREPROCESSOR_CONTROL_IF_HPP
