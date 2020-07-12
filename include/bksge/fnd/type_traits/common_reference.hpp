/**
 *	@file	common_reference.hpp
 *
 *	@brief	common_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_COMMON_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_COMMON_REFERENCE_HPP

namespace bksge
{

template <typename... T>
struct common_reference;

template <typename... T>
using common_reference_t = typename common_reference<T...>::type;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/common_reference_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_COMMON_REFERENCE_HPP
