/**
 *	@file	static_storage.hpp
 *
 *	@brief	static_storage クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_STORAGE_HPP
#define BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_STORAGE_HPP

#include <bksge/fnd/type_traits/aligned_storage.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

template <
	typename T,
	std::size_t N,
	bool = bksge::is_trivially_destructible<T>::value &&
	       bksge::is_default_constructible<T>::value
>
class static_storage
{
private:
	bksge::aligned_storage_t<sizeof(T) * N> m_storage;

public:
	T* get_address()
	{
		return reinterpret_cast<T*>(bksge::addressof(m_storage));
	}
};

template <typename T, std::size_t N>
class static_storage<T, N, true>
{
private:
	T	m_storage[N];

public:
	BKSGE_CXX14_CONSTEXPR static_storage() : m_storage() {}

	BKSGE_CXX14_CONSTEXPR T* get_address()
	{
		return m_storage;
	}
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_STORAGE_HPP
