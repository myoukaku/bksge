/**
 *	@file	cat.hpp
 *
 *	@brief	BKSGE_PP_CAT の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_PREPROCESSOR_CAT_HPP
#define BKSGE_FND_PREPROCESSOR_CAT_HPP
#
# include <bksge/fnd/preprocessor/config/config.hpp>
#
# /* BKSGE_PP_CAT */
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
#    define BKSGE_PP_CAT(a, b) BKSGE_PP_CAT_I(a, b)
# else
#    define BKSGE_PP_CAT(a, b) BKSGE_PP_CAT_OO((a, b))
#    define BKSGE_PP_CAT_OO(par) BKSGE_PP_CAT_I ## par
# endif
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MSVC()
#    define BKSGE_PP_CAT_I(a, b) a ## b
# else
#    define BKSGE_PP_CAT_I(a, b) BKSGE_PP_CAT_II(~, a ## b)
#    define BKSGE_PP_CAT_II(p, res) res
# endif
#
#endif // BKSGE_FND_PREPROCESSOR_CAT_HPP
