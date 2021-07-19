/**
 *	@file	make_any_inl.hpp
 *
 *	@brief	make_any の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ANY_INL_MAKE_ANY_INL_HPP
#define BKSGE_FND_ANY_INL_MAKE_ANY_INL_HPP

#include <bksge/fnd/any/make_any.hpp>
#include <bksge/fnd/any/any.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <initializer_list>
#include <utility>

namespace bksge
{

template <typename T, typename... Args>
inline any make_any(Args&&... args)
{
	return any(bksge::in_place_type_t<T>{}, std::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
inline any make_any(std::initializer_list<U> il, Args&&... args)
{
	return any(bksge::in_place_type_t<T>{}, il, std::forward<Args>(args)...);
}

}	// namespace bksge

#endif // BKSGE_FND_ANY_INL_MAKE_ANY_INL_HPP
