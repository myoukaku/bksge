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
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/initializer_list.hpp>

namespace bksge
{

template <typename T, typename... Args>
inline any make_any(Args&&... args)
{
	return any(bksge::in_place_type_t<T>{}, bksge::forward<Args>(args)...);
}

template <typename T, typename U, typename... Args>
inline any make_any(bksge::initializer_list<U> il, Args&&... args)
{
	return any(bksge::in_place_type_t<T>{}, il, bksge::forward<Args>(args)...);
}

}	// namespace bksge

#endif // BKSGE_FND_ANY_INL_MAKE_ANY_INL_HPP
