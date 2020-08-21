/**
 *	@file	cref.hpp
 *
 *	@brief	cref 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_CREF_HPP
#define BKSGE_FND_FUNCTIONAL_CREF_HPP

#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T>
BKSGE_CONSTEXPR
inline bksge::reference_wrapper<T const>
cref(T const& t) noexcept
{
	return bksge::reference_wrapper<T const>(t);
}

template <typename T>
void cref(T const&&) = delete;

template <typename T>
BKSGE_CONSTEXPR
inline bksge::reference_wrapper<T const>
cref(bksge::reference_wrapper<T> t) noexcept
{
	return { t.get() };
}

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_CREF_HPP
