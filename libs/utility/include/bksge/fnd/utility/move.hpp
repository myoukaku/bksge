/**
 *	@file	move.hpp
 *
 *	@brief	move を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_MOVE_HPP
#define BKSGE_FND_UTILITY_MOVE_HPP

#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T>
inline BKSGE_CONSTEXPR bksge::remove_reference_t<T>&&
move(T&& x) BKSGE_NOEXCEPT
{
	return static_cast<bksge::remove_reference_t<T>&&>(x);
}

}	// namespace bksge

#endif // BKSGE_FND_UTILITY_MOVE_HPP
