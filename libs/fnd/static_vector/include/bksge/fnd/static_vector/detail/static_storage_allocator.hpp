/**
 *	@file	static_storage_allocator.hpp
 *
 *	@brief	static_storage_allocator クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_STORAGE_ALLOCATOR_HPP
#define BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_STORAGE_ALLOCATOR_HPP

#include <bksge/fnd/static_vector/detail/static_storage.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bksge::size_t N>
class static_storage_allocator
{
private:
	static_storage<T, N> m_storage;

public:
	using value_type = T;

	BKSGE_CXX14_CONSTEXPR static_storage_allocator() {}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR static_storage_allocator(static_storage_allocator<U, N> const&) {}

	BKSGE_CXX14_CONSTEXPR T* allocate(bksge::size_t)
	{
		return m_storage.get_address();
	}

	BKSGE_CXX14_CONSTEXPR void deallocate(T*, bksge::size_t) {}
};

template <typename T>
class static_storage_allocator<T, 0>
{
public:
	using value_type = T;

	BKSGE_CXX14_CONSTEXPR static_storage_allocator() {}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR static_storage_allocator(static_storage_allocator<U, 0> const&) {}

	BKSGE_CXX14_CONSTEXPR T* allocate(bksge::size_t) { return nullptr; }

	BKSGE_CXX14_CONSTEXPR void deallocate(T*, bksge::size_t) {}
};

template <typename T, bksge::size_t N>
bool operator==(static_storage_allocator<T, N> const&, static_storage_allocator<T, N> const&)
{
	return true;
}

template <typename T, bksge::size_t N>
bool operator!=(static_storage_allocator<T, N> const&, static_storage_allocator<T, N> const&)
{
	return false;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STATIC_VECTOR_DETAIL_STATIC_STORAGE_ALLOCATOR_HPP
