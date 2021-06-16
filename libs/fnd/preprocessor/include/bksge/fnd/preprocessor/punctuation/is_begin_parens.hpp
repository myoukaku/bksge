/**
 *	@file	is_begin_parens.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_PREPROCESSOR_PUNCTUATION_IS_BEGIN_PARENS_HPP
#define BKSGE_FND_PREPROCESSOR_PUNCTUATION_IS_BEGIN_PARENS_HPP

# include <bksge/fnd/preprocessor/config/config.hpp>

#if BKSGE_PP_VARIADICS

#include <bksge/fnd/preprocessor/punctuation/detail/is_begin_parens.hpp>

#if BKSGE_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BKSGE_PP_IS_BEGIN_PARENS(param)         \
    BKSGE_PP_DETAIL_IBP_SPLIT                   \
      (                                         \
      0,                                        \
      BKSGE_PP_DETAIL_IBP_CAT                   \
        (                                       \
        BKSGE_PP_DETAIL_IBP_IS_VARIADIC_R_,     \
        BKSGE_PP_DETAIL_IBP_IS_VARIADIC_C param \
        )                                       \
      )                                         \
/**/

#else

#define BKSGE_PP_IS_BEGIN_PARENS(...)                 \
    BKSGE_PP_DETAIL_IBP_SPLIT                         \
      (                                               \
      0,                                              \
      BKSGE_PP_DETAIL_IBP_CAT                         \
        (                                             \
        BKSGE_PP_DETAIL_IBP_IS_VARIADIC_R_,           \
        BKSGE_PP_DETAIL_IBP_IS_VARIADIC_C __VA_ARGS__ \
        )                                             \
      )                                               \
/**/

#endif /* BKSGE_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
#endif /* BKSGE_PP_VARIADICS */

#endif // BKSGE_FND_PREPROCESSOR_PUNCTUATION_IS_BEGIN_PARENS_HPP
