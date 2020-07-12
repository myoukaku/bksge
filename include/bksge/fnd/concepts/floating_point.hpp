/**
 *	@file	floating_point.hpp
 *
 *	@brief	floating_point の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_FLOATING_POINT_HPP
#define BKSGE_FND_CONCEPTS_FLOATING_POINT_HPP

#include <bksge/fnd/type_traits/is_floating_point.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept floating_point = bksge::is_floating_point<T>::value;

#endif

template <typename T>
struct floating_point_t : public bksge::is_floating_point<T> {};

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_FLOATING_POINT_HPP
