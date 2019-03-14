/**
 *	@file	seq.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_SEQ_SEQ_HPP
#define BKSGE_PREPROCESSOR_SEQ_SEQ_HPP
#
# include <bksge/preprocessor/config/config.hpp>
# include <bksge/preprocessor/seq/elem.hpp>
#
# /* BKSGE_PP_SEQ_HEAD */
#
# define BKSGE_PP_SEQ_HEAD(seq) BKSGE_PP_SEQ_ELEM(0, seq)
#
# /* BKSGE_PP_SEQ_TAIL */
#
# if BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
#    define BKSGE_PP_SEQ_TAIL(seq) BKSGE_PP_SEQ_TAIL_1((seq))
#    define BKSGE_PP_SEQ_TAIL_1(par) BKSGE_PP_SEQ_TAIL_2 ## par
#    define BKSGE_PP_SEQ_TAIL_2(seq) BKSGE_PP_SEQ_TAIL_I ## seq
# elif BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MSVC()
#    define BKSGE_PP_SEQ_TAIL(seq) BKSGE_PP_SEQ_TAIL_ID(BKSGE_PP_SEQ_TAIL_I seq)
#    define BKSGE_PP_SEQ_TAIL_ID(id) id
# elif BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_EDG()
#    define BKSGE_PP_SEQ_TAIL(seq) BKSGE_PP_SEQ_TAIL_D(seq)
#    define BKSGE_PP_SEQ_TAIL_D(seq) BKSGE_PP_SEQ_TAIL_I seq
# else
#    define BKSGE_PP_SEQ_TAIL(seq) BKSGE_PP_SEQ_TAIL_I seq
# endif
#
# define BKSGE_PP_SEQ_TAIL_I(x)
#
# /* BKSGE_PP_SEQ_NIL */
#
# define BKSGE_PP_SEQ_NIL(x) (x)
#
#endif // BKSGE_PREPROCESSOR_SEQ_SEQ_HPP
