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

#define BKSGE_REQUIRE(C, T)	C T

#else

#define BKSGE_REQUIRE(C, T)	typename T, typename = bksge::enable_if_t<C<T>::value>

#endif

#endif // BKSGE_FND_CONCEPTS_DETAIL_REQUIRE_HPP
