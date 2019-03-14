/**
 *	@file	comma_if.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#define BKSGE_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
#
# include <bksge/preprocessor/config/config.hpp>
# include <bksge/preprocessor/control/if.hpp>
# include <bksge/preprocessor/facilities/empty.hpp>
# include <bksge/preprocessor/punctuation/comma.hpp>
#
# /* BKSGE_PP_COMMA_IF */
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_EDG()
#    define BKSGE_PP_COMMA_IF(cond) BKSGE_PP_IF(cond, BKSGE_PP_COMMA, BKSGE_PP_EMPTY)()
# else
#    define BKSGE_PP_COMMA_IF(cond) BKSGE_PP_COMMA_IF_I(cond)
#    define BKSGE_PP_COMMA_IF_I(cond) BKSGE_PP_IF(cond, BKSGE_PP_COMMA, BKSGE_PP_EMPTY)()
# endif
#
#endif // BKSGE_PREPROCESSOR_PUNCTUATION_COMMA_IF_HPP
