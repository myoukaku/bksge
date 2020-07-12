/**
 *	@file	integral.hpp
 *
 *	@brief	integral の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_INTEGRAL_HPP
#define BKSGE_FND_CONCEPTS_INTEGRAL_HPP

#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept integral = bksge::is_integral<T>::value;

#endif

template <typename T>
struct integral_t : public bksge::is_integral<T> {};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_INTEGRAL_HPP
