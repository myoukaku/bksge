/**
 *	@file	require.hpp
 *
 *	@brief	require の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_REQUIRE_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_REQUIRE_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

#define BKSGE_REQUIRES(...)					requires (__VA_ARGS__)
#define BKSGE_REQUIRES_PARAM(C, T)			C T
#define BKSGE_REQUIRES_PARAM_D(C, T, D)		C T = D
#define BKSGE_REQUIRES_PARAM_2(C, T1, T2)	C<T1> T2

#else

#define BKSGE_REQUIRES(...)
#define BKSGE_REQUIRES_PARAM(C, T)			typename T, typename = bksge::enable_if_t<C<T>::value>
#define BKSGE_REQUIRES_PARAM_D(C, T, D)		typename T = D, typename = bksge::enable_if_t<C<T>::value>
#define BKSGE_REQUIRES_PARAM_2(C, T1, T2)	typename T2, typename = bksge::enable_if_t<C<T2, T1>::value>

#endif

#endif // BKSGE_FND_CONCEPTS_DETAIL_REQUIRE_HPP
