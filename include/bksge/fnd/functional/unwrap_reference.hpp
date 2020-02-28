/**
 *	@file	unwrap_reference.hpp
 *
 *	@brief	unwrap_reference クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_UNWRAP_REFERENCE_HPP
#define BKSGE_FND_FUNCTIONAL_UNWRAP_REFERENCE_HPP

#include <bksge/fnd/functional/reference_wrapper.hpp>

namespace bksge
{

template <typename T>
struct unwrap_reference
{
	using type = T;
};

template <typename T>
struct unwrap_reference<bksge::reference_wrapper<T>>
{
	using type = T&;
};

template <typename T>
using unwrap_reference_t = typename unwrap_reference<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_UNWRAP_REFERENCE_HPP
