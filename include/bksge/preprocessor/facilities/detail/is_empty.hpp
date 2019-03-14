/**
 *	@file	is_empty.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_FACILITIES_DETAIL_IS_EMPTY_HPP
#define BKSGE_PREPROCESSOR_FACILITIES_DETAIL_IS_EMPTY_HPP

#include <bksge/preprocessor/punctuation/is_begin_parens.hpp>

#if BKSGE_PP_VARIADICS_MSVC

# pragma warning(once:4002)

#define BKSGE_PP_DETAIL_IS_EMPTY_IIF_0(t, b) b
#define BKSGE_PP_DETAIL_IS_EMPTY_IIF_1(t, b) t

#else

#define BKSGE_PP_DETAIL_IS_EMPTY_IIF_0(t, ...) __VA_ARGS__
#define BKSGE_PP_DETAIL_IS_EMPTY_IIF_1(t, ...) t

#endif

#if BKSGE_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BKSGE_PP_DETAIL_IS_EMPTY_PROCESS(param)          \
	BKSGE_PP_IS_BEGIN_PARENS                             \
    	(                                                \
        BKSGE_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C param () \
        )                                                \
/**/

#else

#define BKSGE_PP_DETAIL_IS_EMPTY_PROCESS(...)                  \
	BKSGE_PP_IS_BEGIN_PARENS                                   \
        (                                                      \
        BKSGE_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C __VA_ARGS__ () \
        )                                                      \
/**/

#endif

#define BKSGE_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(a, b) a ## b
#define BKSGE_PP_DETAIL_IS_EMPTY_IIF(bit) BKSGE_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(BKSGE_PP_DETAIL_IS_EMPTY_IIF_,bit)
#define BKSGE_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C(...) ()

#endif // BKSGE_PREPROCESSOR_FACILITIES_DETAIL_IS_EMPTY_HPP
