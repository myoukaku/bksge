/**
 *	@file	is_empty_variadic.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
#define BKSGE_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP

# include <bksge/preprocessor/config/config.hpp>

# if BKSGE_PP_VARIADICS

# include <bksge/preprocessor/punctuation/is_begin_parens.hpp>
# include <bksge/preprocessor/facilities/detail/is_empty.hpp>

#if BKSGE_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BKSGE_PP_IS_EMPTY(param)       \
    BKSGE_PP_DETAIL_IS_EMPTY_IIF       \
      (                                \
      BKSGE_PP_IS_BEGIN_PARENS         \
        (                              \
        param                          \
        )                              \
      )                                \
      (                                \
      BKSGE_PP_IS_EMPTY_ZERO,          \
      BKSGE_PP_DETAIL_IS_EMPTY_PROCESS \
      )                                \
    (param)                            \
/**/
#define BKSGE_PP_IS_EMPTY_ZERO(param) 0

# else

#define BKSGE_PP_IS_EMPTY(...)         \
    BKSGE_PP_DETAIL_IS_EMPTY_IIF       \
      (                                \
      BKSGE_PP_IS_BEGIN_PARENS         \
        (                              \
        __VA_ARGS__                    \
        )                              \
      )                                \
      (                                \
      BKSGE_PP_IS_EMPTY_ZERO,          \
      BKSGE_PP_DETAIL_IS_EMPTY_PROCESS \
      )                                \
    (__VA_ARGS__)                      \
/**/
#define BKSGE_PP_IS_EMPTY_ZERO(...) 0

# endif /* BKSGE_PP_VARIADICS_MSVC && _MSC_VER <= 1400 */
# endif /* BKSGE_PP_VARIADICS */

#endif // BKSGE_PREPROCESSOR_FACILITIES_IS_EMPTY_VARIADIC_HPP
