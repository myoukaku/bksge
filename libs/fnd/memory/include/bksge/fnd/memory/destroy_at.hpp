/**
 *	@file	destroy_at.hpp
 *
 *	@brief	destroy_at を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_DESTROY_AT_HPP
#define BKSGE_FND_MEMORY_DESTROY_AT_HPP

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T>
BKSGE_CXX14_CONSTEXPR void destroy_at(T* p);

namespace detail
{

template <bool>
struct destroy_at_impl
{
	template <typename T>
	static BKSGE_CXX14_CONSTEXPR void
	destroy(T* p)
	{
		p->~T();
	}
};

template <>
struct destroy_at_impl<true>
{
	template <typename T>
	static BKSGE_CXX14_CONSTEXPR void
	destroy(T* p)
	{
		for (auto& x : *p)
		{
			bksge::destroy_at(bksge::addressof(x));
		}
	}
};

}	// namespace detail

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
destroy_at(T* p)
{
	detail::destroy_at_impl<
		bksge::is_array<T>::value
	>::destroy(p);
}

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_DESTROY_AT_HPP
