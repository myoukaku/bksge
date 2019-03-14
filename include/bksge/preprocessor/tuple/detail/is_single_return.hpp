/**
 *	@file	is_single_return.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#define BKSGE_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <bksge/preprocessor/config/config.hpp>
#
# /* BKSGE_PP_TUPLE_IS_SINGLE_RETURN */
#
# if BKSGE_PP_VARIADICS && BKSGE_PP_VARIADICS_MSVC
# include <bksge/preprocessor/control/iif.hpp>
# include <bksge/preprocessor/facilities/is_1.hpp>
# include <bksge/preprocessor/tuple/size.hpp>
# define BKSGE_PP_TUPLE_IS_SINGLE_RETURN(sr,nsr,tuple)	\
	BKSGE_PP_IIF(BKSGE_PP_IS_1(BKSGE_PP_TUPLE_SIZE(tuple)),sr,nsr) \
	/**/
# endif /* BKSGE_PP_VARIADICS && BKSGE_PP_VARIADICS_MSVC */
#
#endif // BKSGE_PREPROCESSOR_TUPLE_DETAIL_IS_SINGLE_RETURN_HPP
