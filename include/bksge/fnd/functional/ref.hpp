/**
 *	@file	ref.hpp
 *
 *	@brief	ref 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_REF_HPP
#define BKSGE_FND_FUNCTIONAL_REF_HPP

#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T>
BKSGE_CONSTEXPR
inline bksge::reference_wrapper<T>
ref(T& t) noexcept
{
	return bksge::reference_wrapper<T>(t);
}

template <typename T>
void ref(T const&&) = delete;

template <typename T>
BKSGE_CONSTEXPR
inline bksge::reference_wrapper<T>
ref(bksge::reference_wrapper<T> t) noexcept
{
	return t;
}

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_REF_HPP
