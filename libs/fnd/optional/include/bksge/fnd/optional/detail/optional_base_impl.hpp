/**
 *	@file	optional_base_impl.hpp
 *
 *	@brief	optional_base_impl クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_IMPL_HPP
#define BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_IMPL_HPP

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/assert.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

// Common base class for optional_base<T> to avoid repeating these
// member functions in each specialization.
template <typename T, typename D>
class optional_base_impl
{
protected:
	using stored_type = bksge::remove_const_t<T>;

	// The construct operation has !m_engaged as a precondition
	// while destruct has m_engaged as a precondition.
	template <typename... Args>
	void construct(Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<stored_type, Args...>::value))
	{
		::new (bksge::addressof(static_cast<D*>(this)->m_payload.m_payload))
			stored_type(std::forward<Args>(args)...);
		static_cast<D*>(this)->m_payload.m_engaged = true;
	}

	void destruct() BKSGE_NOEXCEPT
	{
		static_cast<D*>(this)->m_payload.destroy();
	}

	// reset_impl is a 'safe' operation with no precondition.
	BKSGE_CXX14_CONSTEXPR void reset_impl() BKSGE_NOEXCEPT
	{
		static_cast<D*>(this)->m_payload.reset_impl();
	}

	BKSGE_CONSTEXPR bool is_engaged() const BKSGE_NOEXCEPT
	{
		return static_cast<D const*>(this)->m_payload.m_engaged;
	}

	// The get operations have m_engaged as a precondition.
	BKSGE_CXX14_CONSTEXPR T& get() BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT(this->is_engaged()),
			static_cast<D*>(this)->m_payload.get();
	}

	BKSGE_CONSTEXPR T const& get() const BKSGE_NOEXCEPT
	{
		return
			BKSGE_ASSERT(this->is_engaged()),
			static_cast<D const*>(this)->m_payload.get();
	}
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_IMPL_HPP
