/**
 *	@file	stringize.hpp
 *
 *	@brief	BKSGE_PP_STRINGIZE の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_STRINGIZE_HPP
#define BKSGE_PREPROCESSOR_STRINGIZE_HPP
#
# include <bksge/preprocessor/config/config.hpp>
#
# /* BKSGE_PP_STRINGIZE */
#
# if BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MSVC()
#    define BKSGE_PP_STRINGIZE(text) BKSGE_PP_STRINGIZE_A((text))
#    define BKSGE_PP_STRINGIZE_A(arg) BKSGE_PP_STRINGIZE_I arg
# elif BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
#    define BKSGE_PP_STRINGIZE(text) BKSGE_PP_STRINGIZE_OO((text))
#    define BKSGE_PP_STRINGIZE_OO(par) BKSGE_PP_STRINGIZE_I ## par
# else
#    define BKSGE_PP_STRINGIZE(text) BKSGE_PP_STRINGIZE_I(text)
# endif
#
# define BKSGE_PP_STRINGIZE_I(text) #text
#
#endif // BKSGE_PREPROCESSOR_STRINGIZE_HPP
