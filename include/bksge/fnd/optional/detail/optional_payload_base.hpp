/**
 *	@file	optional_payload_base.hpp
 *
 *	@brief	optional_payload_base クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_PAYLOAD_BASE_HPP
#define BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_PAYLOAD_BASE_HPP

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <initializer_list>

namespace bksge
{

namespace detail
{

// This class template manages construction/destruction of
// the contained value for a bksge::optional.
template <typename T>
struct optional_payload_base
{
	using stored_type = bksge::remove_const_t<T>;

	optional_payload_base() = default;
	~optional_payload_base() = default;

	template <typename... Args>
	BKSGE_CONSTEXPR
	optional_payload_base(bksge::in_place_t tag, Args&&... args)
		: m_payload(tag, bksge::forward<Args>(args)...)
		, m_engaged(true)
	{}

	template <typename U, typename... Args>
	BKSGE_CONSTEXPR
	optional_payload_base(std::initializer_list<U> il, Args&&... args)
		: m_payload(il, bksge::forward<Args>(args)...)
		, m_engaged(true)
	{}

	// Constructor used by optional_base copy constructor when the
	// contained value is not trivially copy constructible.
	BKSGE_CXX14_CONSTEXPR
	optional_payload_base(bool /*engaged*/, optional_payload_base const& other)
	{
		if (other.m_engaged)
		{
			this->construct(other.get());
		}
	}

	// Constructor used by optional_base move constructor when the
	// contained value is not trivially move constructible.
	BKSGE_CXX14_CONSTEXPR
	optional_payload_base(bool /*engaged*/, optional_payload_base&& other)
	{
		if (other.m_engaged)
		{
			this->construct(bksge::move(other.get()));
		}
	}

	// Copy constructor is only used to when the contained value is
	// trivially copy constructible.
	optional_payload_base(optional_payload_base const&) = default;

	// Move constructor is only used to when the contained value is
	// trivially copy constructible.
	optional_payload_base(optional_payload_base&&) = default;

	optional_payload_base&
	operator=(optional_payload_base const&) = default;

	optional_payload_base&
	operator=(optional_payload_base&&) = default;

	// used to perform non-trivial copy assignment.
	BKSGE_CXX14_CONSTEXPR void
	copy_assign(optional_payload_base const& other)
	{
		if (this->m_engaged && other.m_engaged)
		{
			this->get() = other.get();
		}
		else
		{
			if (other.m_engaged)
			{
				this->construct(other.get());
			}
			else
			{
				this->reset_impl();
			}
		}
	}

	// used to perform non-trivial move assignment.
	BKSGE_CXX14_CONSTEXPR void
	move_assign(optional_payload_base&& other)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_move_constructible<T>,
			bksge::is_nothrow_move_assignable<T>>::value))
	{
		if (this->m_engaged && other.m_engaged)
		{
			this->get() = bksge::move(other.get());
		}
		else
		{
			if (other.m_engaged)
			{
				this->construct(bksge::move(other.get()));
			}
			else
			{
				this->reset_impl();
			}
		}
	}

	struct empty_byte {};

	template <typename U, bool = bksge::is_trivially_destructible<U>::value>
	union storage
	{
		BKSGE_CONSTEXPR
		storage() BKSGE_NOEXCEPT
			: m_empty()
		{}

		template <typename... Args>
		BKSGE_CONSTEXPR
		storage(bksge::in_place_t, Args&&... args)
			: m_value(bksge::forward<Args>(args)...)
		{}

		template <typename V, typename... Args>
		BKSGE_CONSTEXPR
		storage(std::initializer_list<V> il, Args&&... args)
			: m_value(il, bksge::forward<Args>(args)...)
		{}

		empty_byte m_empty;
		U m_value;
	};

	template <typename U>
	union storage<U, false>
	{
		BKSGE_CONSTEXPR
		storage() BKSGE_NOEXCEPT
			: m_empty()
		{}

		template <typename... Args>
		BKSGE_CONSTEXPR
		storage(bksge::in_place_t, Args&&... args)
			: m_value(bksge::forward<Args>(args)...)
		{}

		template <typename V, typename... Args>
		BKSGE_CONSTEXPR
		storage(std::initializer_list<V> il, Args&&... args)
			: m_value(il, bksge::forward<Args>(args)...)
		{}

		// User-provided destructor is needed when U has non-trivial dtor.
		~storage() {}

		empty_byte m_empty;
		U m_value;
	};

	storage<stored_type> m_payload;

	bool m_engaged = false;

	template <typename... Args>
	void construct(Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<stored_type, Args...>::value))
	{
		::new ((void*)bksge::addressof(this->m_payload))stored_type(bksge::forward<Args>(args)...);
		this->m_engaged = true;
	}

	BKSGE_CXX14_CONSTEXPR void destroy() BKSGE_NOEXCEPT
	{
		m_engaged = false;
		m_payload.m_value.~stored_type();
	}

	// The get() operations have m_engaged as a precondition.
	// They exist to access the contained value with the appropriate
	// const-qualification, because m_payload has had the const removed.

	BKSGE_CXX14_CONSTEXPR T& get() BKSGE_NOEXCEPT
	{
		return this->m_payload.m_value;
	}

	BKSGE_CONSTEXPR T const& get() const BKSGE_NOEXCEPT
	{
		return this->m_payload.m_value;
	}

	// reset_impl is a 'safe' operation with no precondition.
	BKSGE_CXX14_CONSTEXPR void reset_impl() BKSGE_NOEXCEPT
	{
		if (this->m_engaged)
		{
			destroy();
		}
	}
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_PAYLOAD_BASE_HPP
