/**
 *	@file	size.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_PREPROCESSOR_TUPLE_SIZE_HPP
#define BKSGE_FND_PREPROCESSOR_TUPLE_SIZE_HPP
#
# include <bksge/fnd/preprocessor/cat.hpp>
# include <bksge/fnd/preprocessor/config/config.hpp>
# include <bksge/fnd/preprocessor/variadic/size.hpp>
#
# if BKSGE_PP_VARIADICS
#    if BKSGE_PP_VARIADICS_MSVC
#        define BKSGE_PP_TUPLE_SIZE(tuple) BKSGE_PP_CAT(BKSGE_PP_VARIADIC_SIZE tuple,)
#    else
#        define BKSGE_PP_TUPLE_SIZE(tuple) BKSGE_PP_VARIADIC_SIZE tuple
#    endif
# endif
#
#endif // BKSGE_FND_PREPROCESSOR_TUPLE_SIZE_HPP
