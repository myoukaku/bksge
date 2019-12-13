/**
 *	@file	is_1.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_PREPROCESSOR_FACILITIES_IS_1_HPP
#define BKSGE_FND_PREPROCESSOR_FACILITIES_IS_1_HPP
#
# include <bksge/fnd/preprocessor/cat.hpp>
# include <bksge/fnd/preprocessor/facilities/is_empty.hpp>
#
# /* BKSGE_PP_IS_1 */
#
# define BKSGE_PP_IS_1(x) BKSGE_PP_IS_EMPTY(BKSGE_PP_CAT(BKSGE_PP_IS_1_HELPER_, x))
# define BKSGE_PP_IS_1_HELPER_1
#
#endif // BKSGE_FND_PREPROCESSOR_FACILITIES_IS_1_HPP
