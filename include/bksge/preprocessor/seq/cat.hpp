﻿/**
 *	@file	cat.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_SEQ_CAT_HPP
#define BKSGE_PREPROCESSOR_SEQ_CAT_HPP
#
# include <bksge/preprocessor/arithmetic/dec.hpp>
# include <bksge/preprocessor/config/config.hpp>
# include <bksge/preprocessor/control/if.hpp>
# include <bksge/preprocessor/seq/fold_left.hpp>
# include <bksge/preprocessor/seq/seq.hpp>
# include <bksge/preprocessor/seq/size.hpp>
# include <bksge/preprocessor/tuple/eat.hpp>
#
# /* BKSGE_PP_SEQ_CAT */
#
# define BKSGE_PP_SEQ_CAT(seq)                \
    BKSGE_PP_IF(                              \
        BKSGE_PP_DEC(BKSGE_PP_SEQ_SIZE(seq)), \
        BKSGE_PP_SEQ_CAT_I,                   \
        BKSGE_PP_SEQ_HEAD                     \
    )(seq)                                    \
    /**/
# define BKSGE_PP_SEQ_CAT_I(seq) BKSGE_PP_SEQ_FOLD_LEFT(BKSGE_PP_SEQ_CAT_O, BKSGE_PP_SEQ_HEAD(seq), BKSGE_PP_SEQ_TAIL(seq))
#
# define BKSGE_PP_SEQ_CAT_O(s, st, elem) BKSGE_PP_SEQ_CAT_O_I(st, elem)
# define BKSGE_PP_SEQ_CAT_O_I(a, b) a ## b
#
# /* BKSGE_PP_SEQ_CAT_S */
#
# define BKSGE_PP_SEQ_CAT_S(s, seq)           \
    BKSGE_PP_IF(                              \
        BKSGE_PP_DEC(BKSGE_PP_SEQ_SIZE(seq)), \
        BKSGE_PP_SEQ_CAT_S_I_A,               \
        BKSGE_PP_SEQ_CAT_S_I_B                \
    )(s, seq)                                 \
    /**/
# define BKSGE_PP_SEQ_CAT_S_I_A(s, seq) BKSGE_PP_SEQ_FOLD_LEFT_ ## s(BKSGE_PP_SEQ_CAT_O, BKSGE_PP_SEQ_HEAD(seq), BKSGE_PP_SEQ_TAIL(seq))
# define BKSGE_PP_SEQ_CAT_S_I_B(s, seq) BKSGE_PP_SEQ_HEAD(seq)
#
#endif // BKSGE_PREPROCESSOR_SEQ_CAT_HPP
