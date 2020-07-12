/**
 *	@file	destructible.hpp
 *
 *	@brief	destructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DESTRUCTIBLE_HPP
#define BKSGE_FND_CONCEPTS_DESTRUCTIBLE_HPP

#include <bksge/fnd/type_traits/is_nothrow_destructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept destructible = bksge::is_nothrow_destructible<T>::value;

#endif

template <typename T>
struct destructible_t : public bksge::is_nothrow_destructible<T> {};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DESTRUCTIBLE_HPP
