/**
 *	@file	uninitialized.hpp
 *
 *	@brief	Uninitialized の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_UNINITIALIZED_HPP
#define BKSGE_FND_VARIANT_DETAIL_UNINITIALIZED_HPP

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/aligned_storage.hpp>
#include <bksge/fnd/type_traits/alignment_of.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace variant_detail
{

// Uninitialized<T> is guaranteed to be a trivially destructible type,
// even if T is not.
template <typename Type, bool = bksge::is_trivially_destructible<Type>::value>
struct Uninitialized;

template <typename Type>
struct Uninitialized<Type, true>
{
	template <typename... Args>
	BKSGE_CONSTEXPR
	Uninitialized(bksge::in_place_index_t<0>, Args&&... args)
		: m_storage(std::forward<Args>(args)...)
	{}

	BKSGE_CONSTEXPR Type const& get() const& noexcept
	{
		return m_storage;
	}

	BKSGE_CXX14_CONSTEXPR Type& get() & noexcept
	{
		return m_storage;
	}

	BKSGE_CXX14_CONSTEXPR Type const&& get() const&& noexcept
	{
		return std::move(m_storage);
	}

	BKSGE_CXX14_CONSTEXPR Type&& get() && noexcept
	{
		return std::move(m_storage);
	}

private:
	Type m_storage;
};

template <typename Type>
struct Uninitialized<Type, false>
{
	template <typename... Args>
	/*constexpr*/
	Uninitialized(bksge::in_place_index_t<0>, Args&&... args)
	{
		::new ((void*)bksge::addressof(m_storage)) Type(std::forward<Args>(args)...);
	}

	Type const& get() const& noexcept
	{
		return *addr();
	}

	Type& get() & noexcept
	{
		return *addr();
	}

	Type const&& get() const&& noexcept
	{
		return std::move(*addr());
	}

	Type&& get() && noexcept
	{
		return std::move(*addr());
	}

private:
	Type const* addr() const noexcept
	{
		return static_cast<Type const*>(static_cast<void const*>(&m_storage));
	}

	Type* addr() noexcept
	{
		return static_cast<Type*>(static_cast<void*>(&m_storage));
	}

	bksge::aligned_storage_t<sizeof(Type), bksge::alignment_of<Type>::value> m_storage;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_UNINITIALIZED_HPP
