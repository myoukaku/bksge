/**
 *	@file	is_empty.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#define BKSGE_FND_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
#
# include <bksge/fnd/preprocessor/config/config.hpp>
#
# if BKSGE_PP_VARIADICS
#
# include <bksge/fnd/preprocessor/facilities/is_empty_variadic.hpp>
#
# else
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MSVC() && ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
# include <bksge/fnd/preprocessor/tuple/elem.hpp>
# include <bksge/fnd/preprocessor/facilities/identity.hpp>
# else
# include <bksge/fnd/preprocessor/cat.hpp>
# include <bksge/fnd/preprocessor/detail/split.hpp>
# endif
#
# /* BKSGE_PP_IS_EMPTY */
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MSVC() && ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
#    define BKSGE_PP_IS_EMPTY(x) BKSGE_PP_IS_EMPTY_I(x BKSGE_PP_IS_EMPTY_HELPER)
#    define BKSGE_PP_IS_EMPTY_I(contents) BKSGE_PP_TUPLE_ELEM(2, 1, (BKSGE_PP_IS_EMPTY_DEF_ ## contents()))
#    define BKSGE_PP_IS_EMPTY_DEF_BKSGE_PP_IS_EMPTY_HELPER 1, BKSGE_PP_IDENTITY(1)
#    define BKSGE_PP_IS_EMPTY_HELPER() , 0
# else
#    if BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MSVC()
#        define BKSGE_PP_IS_EMPTY(x) BKSGE_PP_IS_EMPTY_I(BKSGE_PP_IS_EMPTY_HELPER x ())
#        define BKSGE_PP_IS_EMPTY_I(test) BKSGE_PP_IS_EMPTY_II(BKSGE_PP_SPLIT(0, BKSGE_PP_CAT(BKSGE_PP_IS_EMPTY_DEF_, test)))
#        define BKSGE_PP_IS_EMPTY_II(id) id
#    else
#        define BKSGE_PP_IS_EMPTY(x) BKSGE_PP_IS_EMPTY_I((BKSGE_PP_IS_EMPTY_HELPER x ()))
#        define BKSGE_PP_IS_EMPTY_I(par) BKSGE_PP_IS_EMPTY_II ## par
#        define BKSGE_PP_IS_EMPTY_II(test) BKSGE_PP_SPLIT(0, BKSGE_PP_CAT(BKSGE_PP_IS_EMPTY_DEF_, test))
#    endif
#    define BKSGE_PP_IS_EMPTY_HELPER() 1
#    define BKSGE_PP_IS_EMPTY_DEF_1 1, BKSGE_PP_NIL
#    define BKSGE_PP_IS_EMPTY_DEF_BKSGE_PP_IS_EMPTY_HELPER 0, BKSGE_PP_NIL
# endif
#
# endif /* BKSGE_PP_VARIADICS */
#
#endif // BKSGE_FND_PREPROCESSOR_FACILITIES_IS_EMPTY_HPP
