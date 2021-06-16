/**
 *	@file	optional_base.hpp
 *
 *	@brief	optional_base クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP
#define BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP

#include <bksge/fnd/optional/detail/optional_base_impl.hpp>
#include <bksge/fnd/optional/detail/optional_payload.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/initializer_list.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

/**
  * @brief Class template that provides copy/move constructors of optional.
  *
  * Such a separate base class template is necessary in order to
  * conditionally make copy/move constructors trivial.
  *
  * When the contained value is trivially copy/move constructible,
  * the copy/move constructors of optional_base will invoke the
  * trivial copy/move constructor of optional_payload. Otherwise,
  * they will invoke optional_payload(bool, optional_payload const&)
  * or optional_payload(bool, optional_payload&&) to initialize
  * the contained value, if copying/moving an engaged optional.
  *
  * Whether the other special members are trivial is determined by the
  * optional_payload<T> specialization used for the m_payload member.
  *
  * @see optional, _Enable_special_members
  */
template <typename T,
	bool = bksge::is_trivially_copy_constructible<T>::value,
	bool = bksge::is_trivially_move_constructible<T>::value>
struct optional_base
	: public optional_base_impl<T, optional_base<T>>
{
	// Constructors for disengaged optionals.
	BKSGE_CONSTEXPR optional_base() = default;

	// Constructors for engaged optionals.
	template <typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, Args&&... args)
		: m_payload(bksge::in_place, bksge::forward<Args>(args)...)
	{}

	template <typename U, typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, bksge::initializer_list<U>&, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, bksge::initializer_list<U> il, Args&&... args)
		: m_payload(bksge::in_place, il, bksge::forward<Args>(args)...)
	{}

	// Copy and move constructors.
	BKSGE_CONSTEXPR
	optional_base(optional_base const& other)
		: m_payload(other.m_payload.m_engaged, other.m_payload)
	{}

	BKSGE_CONSTEXPR
	optional_base(optional_base&& other)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_move_constructible<T>::value))
		: m_payload(other.m_payload.m_engaged, bksge::move(other.m_payload))
	{}

	// Assignment operators.
	optional_base& operator=(optional_base const&) = default;
	optional_base& operator=(optional_base&&) = default;

	optional_payload<T> m_payload;
};

template <typename T>
struct optional_base<T, false, true>
	: public optional_base_impl<T, optional_base<T>>
{
	// Constructors for disengaged optionals.
	BKSGE_CONSTEXPR optional_base() = default;

	// Constructors for engaged optionals.
	template <typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, Args&&... args)
		: m_payload(bksge::in_place, bksge::forward<Args>(args)...)
	{}

	template <typename U, typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, bksge::initializer_list<U>&, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, bksge::initializer_list<U> il, Args... args)
		: m_payload(bksge::in_place, il, bksge::forward<Args>(args)...)
	{}

	// Copy and move constructors.
	BKSGE_CONSTEXPR optional_base(optional_base const& other)
		: m_payload(other.m_payload.m_engaged, other.m_payload)
	{}

	BKSGE_CONSTEXPR optional_base(optional_base&& other) = default;

	// Assignment operators.
	optional_base& operator=(optional_base const&) = default;
	optional_base& operator=(optional_base&&) = default;

	optional_payload<T> m_payload;
};

template <typename T>
struct optional_base<T, true, false>
	: public optional_base_impl<T, optional_base<T>>
{
	// Constructors for disengaged optionals.
	BKSGE_CONSTEXPR optional_base() = default;

	// Constructors for engaged optionals.
	template <typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, Args&&... args)
		: m_payload(bksge::in_place, bksge::forward<Args>(args)...)
	{}

	template <typename U, typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, bksge::initializer_list<U>&, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, bksge::initializer_list<U> il, Args&&... args)
		: m_payload(bksge::in_place, il, bksge::forward<Args>(args)...)
	{}

	// Copy and move constructors.
	BKSGE_CONSTEXPR optional_base(optional_base const& other) = default;

	BKSGE_CONSTEXPR
	optional_base(optional_base&& other)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_move_constructible<T>::value))
		: m_payload(other.m_payload.m_engaged, bksge::move(other.m_payload))
	{}

	// Assignment operators.
	optional_base& operator=(optional_base const&) = default;
	optional_base& operator=(optional_base&&) = default;

	optional_payload<T> m_payload;
};

template <typename T>
struct optional_base<T, true, true>
	: public optional_base_impl<T, optional_base<T>>
{
	// Constructors for disengaged optionals.
	BKSGE_CONSTEXPR optional_base() = default;

	// Constructors for engaged optionals.
	template <typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, Args&&... args)
		: m_payload(bksge::in_place, bksge::forward<Args>(args)...)
	{}

	template <typename U, typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, bksge::initializer_list<U>&, Args...>::value>>
	BKSGE_CONSTEXPR explicit
	optional_base(bksge::in_place_t, bksge::initializer_list<U> il, Args&&... args)
		: m_payload(bksge::in_place, il, bksge::forward<Args>(args)...)
	{}

	// Copy and move constructors.
	BKSGE_CONSTEXPR optional_base(optional_base const& other) = default;
	BKSGE_CONSTEXPR optional_base(optional_base&& other) = default;

	// Assignment operators.
	optional_base& operator=(optional_base const&) = default;
	optional_base& operator=(optional_base&&) = default;

	optional_payload<T> m_payload;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP
