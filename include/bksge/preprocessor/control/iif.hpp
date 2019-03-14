/**
 *	@file	iif.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_CONTROL_IIF_HPP
#define BKSGE_PREPROCESSOR_CONTROL_IIF_HPP
#
# include <bksge/preprocessor/config/config.hpp>
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
#    define BKSGE_PP_IIF(bit, t, f) BKSGE_PP_IIF_I(bit, t, f)
# else
#    define BKSGE_PP_IIF(bit, t, f) BKSGE_PP_IIF_OO((bit, t, f))
#    define BKSGE_PP_IIF_OO(par) BKSGE_PP_IIF_I ## par
# endif
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MSVC()
#    define BKSGE_PP_IIF_I(bit, t, f) BKSGE_PP_IIF_ ## bit(t, f)
# else
#    define BKSGE_PP_IIF_I(bit, t, f) BKSGE_PP_IIF_II(BKSGE_PP_IIF_ ## bit(t, f))
#    define BKSGE_PP_IIF_II(id) id
# endif
#
# define BKSGE_PP_IIF_0(t, f) f
# define BKSGE_PP_IIF_1(t, f) t
#
#endif // BKSGE_PREPROCESSOR_CONTROL_IIF_HPP
