/**
 *	@file	construct_at.hpp
 *
 *	@brief	construct_at を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_CONSTRUCT_AT_HPP
#define BKSGE_FND_MEMORY_CONSTRUCT_AT_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T, typename... Args>
inline BKSGE_CXX14_CONSTEXPR auto
construct_at(T* p, Args&&... args)
noexcept(noexcept(::new(const_cast<void*>(static_cast<const volatile void*>(p))) T(bksge::forward<Args>(args)...)))
->decltype(::new(const_cast<void*>(static_cast<const volatile void*>(p))) T(bksge::forward<Args>(args)...))
{
	return ::new(const_cast<void*>(static_cast<const volatile void*>(p))) T(bksge::forward<Args>(args)...);
}

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_CONSTRUCT_AT_HPP
