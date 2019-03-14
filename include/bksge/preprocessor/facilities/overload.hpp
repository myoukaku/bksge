/**
 *	@file	overload.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#define BKSGE_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <bksge/preprocessor/cat.hpp>
# include <bksge/preprocessor/variadic/size.hpp>
#
# /* BKSGE_PP_OVERLOAD */
#
# if BKSGE_PP_VARIADICS
#    define BKSGE_PP_OVERLOAD(prefix, ...) BKSGE_PP_CAT(prefix, BKSGE_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
#endif // BKSGE_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
