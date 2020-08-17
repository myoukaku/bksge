/**
 *	@file	object.hpp
 *
 *	@brief	object の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_OBJECT_HPP
#define BKSGE_FND_RANGES_DETAIL_OBJECT_HPP

#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept object = bksge::is_object<T>::value;

#else

template <typename T>
using object = bksge::is_object<T>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_OBJECT_HPP
