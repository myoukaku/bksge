/**
 *	@file	if.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_PREPROCESSOR_CONTROL_IF_HPP
#define BKSGE_FND_PREPROCESSOR_CONTROL_IF_HPP
#
# include <bksge/fnd/preprocessor/config/config.hpp>
# include <bksge/fnd/preprocessor/control/iif.hpp>
# include <bksge/fnd/preprocessor/logical/bool.hpp>
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
#endif // BKSGE_FND_PREPROCESSOR_CONTROL_IF_HPP
