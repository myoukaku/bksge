/**
 *	@file	expand.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_FACILITIES_EXPAND_HPP
#define BKSGE_PREPROCESSOR_FACILITIES_EXPAND_HPP
#
# include <bksge/preprocessor/config/config.hpp>
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC() && ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_DMC()
#    define BKSGE_PP_EXPAND(x) BKSGE_PP_EXPAND_I(x)
# else
#    define BKSGE_PP_EXPAND(x) BKSGE_PP_EXPAND_OO((x))
#    define BKSGE_PP_EXPAND_OO(par) BKSGE_PP_EXPAND_I ## par
# endif
#
# define BKSGE_PP_EXPAND_I(x) x
#
#endif // BKSGE_PREPROCESSOR_FACILITIES_EXPAND_HPP
