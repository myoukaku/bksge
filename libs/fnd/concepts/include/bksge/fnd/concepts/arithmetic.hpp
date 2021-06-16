/**
 *	@file	arithmetic.hpp
 *
 *	@brief	arithmetic の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_ARITHMETIC_HPP
#define BKSGE_FND_CONCEPTS_ARITHMETIC_HPP

#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept arithmetic = bksge::is_arithmetic<T>::value;

#else

template <typename T>
using arithmetic = bksge::is_arithmetic<T>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_ARITHMETIC_HPP
