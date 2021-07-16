/**
 *	@file	optional_payload.hpp
 *
 *	@brief	optional_payload クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_PAYLOAD_HPP
#define BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_PAYLOAD_HPP

#include <bksge/fnd/optional/detail/optional_payload_base.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

// Class template that manages the payload for optionals.
template <typename T,
	bool HasTrivialDestructor = bksge::is_trivially_destructible<T>::value,
	bool HasTrivialCopy       = bksge::is_trivially_copy_assignable<T>::value &&
	                            bksge::is_trivially_copy_constructible<T>::value,
	bool HasTrivialMove       = bksge::is_trivially_move_assignable<T>::value &&
	                            bksge::is_trivially_move_constructible<T>::value>
struct optional_payload;

// Payload for potentially-constexpr optionals (trivial copy/move/destroy).
template <typename T>
struct optional_payload<T, true, true, true>
	: public optional_payload_base<T>
{
	using optional_payload_base<T>::optional_payload_base;

	optional_payload() = default;
};

// Payload for optionals with non-trivial copy construction/assignment.
template <typename T>
struct optional_payload<T, true, false, true>
	: public optional_payload_base<T>
{
	using optional_payload_base<T>::optional_payload_base;

	optional_payload() = default;
	~optional_payload() = default;
	optional_payload(optional_payload const&) = default;
	optional_payload(optional_payload&&) = default;
	optional_payload& operator=(optional_payload&&) = default;

	// Non-trivial copy assignment.
	BKSGE_CXX14_CONSTEXPR
	optional_payload& operator=(optional_payload const& other)
	{
		this->copy_assign(other);
		return *this;
	}
};

// Payload for optionals with non-trivial move construction/assignment.
template <typename T>
struct optional_payload<T, true, true, false>
	: public optional_payload_base<T>
{
	using optional_payload_base<T>::optional_payload_base;

	optional_payload() = default;
	~optional_payload() = default;
	optional_payload(optional_payload const&) = default;
	optional_payload(optional_payload&&) = default;
	optional_payload& operator=(optional_payload const&) = default;

	// Non-trivial move assignment.
	BKSGE_CXX14_CONSTEXPR
	optional_payload& operator=(optional_payload&& other)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_move_constructible<T>,
			bksge::is_nothrow_move_assignable<T>>::value))
	{
		this->move_assign(std::move(other));
		return *this;
	}
};

// Payload for optionals with non-trivial copy and move assignment.
template <typename T>
struct optional_payload<T, true, false, false>
	: public optional_payload_base<T>
{
	using optional_payload_base<T>::optional_payload_base;

	optional_payload() = default;
	~optional_payload() = default;
	optional_payload(optional_payload const&) = default;
	optional_payload(optional_payload&&) = default;

	// Non-trivial copy assignment.
	BKSGE_CXX14_CONSTEXPR
	optional_payload& operator=(optional_payload const& other)
	{
		this->copy_assign(other);
		return *this;
	}

	// Non-trivial move assignment.
	BKSGE_CXX14_CONSTEXPR
	optional_payload& operator=(optional_payload&& other)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_move_constructible<T>,
			bksge::is_nothrow_move_assignable<T>>::value))
	{
		this->move_assign(std::move(other));
		return *this;
	}
};

// Payload for optionals with non-trivial destructors.
template <typename T, bool Copy, bool Move>
struct optional_payload<T, false, Copy, Move>
	: public optional_payload<T, true, false, false>
{
	// Base class implements all the constructors and assignment operators:
	using optional_payload<T, true, false, false>::optional_payload;
	optional_payload() = default;
	optional_payload(optional_payload const&) = default;
	optional_payload(optional_payload&&) = default;
	optional_payload& operator=(optional_payload const&) = default;
	optional_payload& operator=(optional_payload&&) = default;

	// Destructor needs to destroy the contained value:
	~optional_payload() { this->reset_impl(); }
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_PAYLOAD_HPP
