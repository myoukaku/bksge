/**
 *	@file	optional.hpp
 *
 *	@brief	optional の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_OPTIONAL_HPP
#define BKSGE_FND_OPTIONAL_OPTIONAL_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 17) && BKSGE_HAS_INCLUDE(<optional>)
#include <optional>
#endif

#if defined(__cpp_lib_optional) && (__cpp_lib_optional >= 201606)

namespace bksge
{

using std::optional;

}	// namespace bksge

#else

#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/optional/detail/optional_base.hpp>
#include <bksge/fnd/detail/enable_copy_move.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <cstddef>
#include <initializer_list>

namespace bksge
{

/**
 * @brief
 */
template <typename T>
class optional
	: private detail::optional_base<T>
	, private detail::enable_copy_move<
		bksge::is_copy_constructible<T>::value,
		bksge::is_copy_constructible<T>::value && bksge::is_copy_assignable<T>::value,
		bksge::is_move_constructible<T>::value,
		bksge::is_move_constructible<T>::value && bksge::is_move_assignable<T>::value,
		optional<T>>
{
	static_assert(
		!bksge::is_same<bksge::remove_cv_t<T>, nullopt_t>::value &&
		!bksge::is_same<bksge::remove_cv_t<T>, in_place_t>::value &&
		!bksge::is_reference<T>::value,
		"Invalid instantiation of optional<T>");

private:
	using base = detail::optional_base<T>;

	struct IsNothrowSwappable;
	struct IsNothrowMoveConstructible;
	struct IsNothrowMoveAssignable;

public:
	using value_type = T;

	BKSGE_CONSTEXPR optional();

	BKSGE_CONSTEXPR optional(nullopt_t) BKSGE_NOEXCEPT;

	BKSGE_CONSTEXPR optional(T const& t);

	BKSGE_CONSTEXPR optional(T&& t);

	template <typename... Args>
	BKSGE_CONSTEXPR explicit
	optional(in_place_t t, Args&&... args);

	template <
		typename U, typename... Args,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, std::initializer_list<U>&, Args&&...>::value
		>
	>
	BKSGE_CONSTEXPR explicit
	optional(in_place_t t, std::initializer_list<U> il, Args&&... args);

#if defined(_MSC_VER) && (_MSC_VER <= 1900)
	BKSGE_CXX14_CONSTEXPR optional(optional const& other);
	BKSGE_CXX14_CONSTEXPR optional(optional&& other) BKSGE_NOEXCEPT_IF(IsNothrowMoveConstructible::value);
#endif

	optional& operator=(nullopt_t) BKSGE_NOEXCEPT;

#if defined(_MSC_VER) && (_MSC_VER <= 1900)
	optional& operator=(optional const& other);
	optional& operator=(optional&& other) BKSGE_NOEXCEPT_IF(IsNothrowMoveAssignable::value);
#endif

	template <
		typename U,
		typename = bksge::enable_if_t<
			bksge::is_same<T, bksge::decay_t<U>>::value
		>
	>
	optional& operator=(U&& u);

	template <typename... Args>
	void emplace(Args&&... args);

	template <
		typename U, typename... Args,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, std::initializer_list<U>&, Args&&...>::value
		>
	>
	void emplace(std::initializer_list<U> il, Args&&... args);

	// Destructor is implicit, implemented in optional_base_impl.

	void swap(optional& other) BKSGE_NOEXCEPT_IF(IsNothrowSwappable::value);

	BKSGE_CONSTEXPR T const* operator->() const;
	BKSGE_CXX14_CONSTEXPR T* operator->();

#if defined(BKSGE_HAS_CXX11_REF_QUALIFIERS)
	BKSGE_CONSTEXPR T const&  operator*() const&;
	BKSGE_CXX14_CONSTEXPR T&  operator*() &;
	BKSGE_CONSTEXPR T const&& operator*() const&&;
	BKSGE_CXX14_CONSTEXPR T&& operator*() &&;
#else
	BKSGE_CONSTEXPR T const& operator*() const;
	BKSGE_CXX14_CONSTEXPR T& operator*();
#endif

	BKSGE_CONSTEXPR explicit operator bool() const BKSGE_NOEXCEPT;

#if defined(BKSGE_HAS_CXX11_REF_QUALIFIERS)
	BKSGE_CONSTEXPR T const&  value() const&;
	BKSGE_CXX14_CONSTEXPR T&  value() &;
	BKSGE_CONSTEXPR T const&& value() const&&;
	BKSGE_CXX14_CONSTEXPR T&& value() &&;
#else
	BKSGE_CONSTEXPR T const& value() const;
	BKSGE_CXX14_CONSTEXPR T& value();
#endif

#if defined(BKSGE_HAS_CXX11_REF_QUALIFIERS)
	template <typename U> BKSGE_CONSTEXPR       T value_or(U&& u) const&;
	template <typename U> BKSGE_CXX14_CONSTEXPR T value_or(U&& u) &&;
#else
	template <typename U> BKSGE_CONSTEXPR       T value_or(U&& u) const;
#endif

private:
	BKSGE_CONSTEXPR bool engaged_check() const;
};

// [X.Y.8] Comparisons between optional values.
template <typename T> BKSGE_CONSTEXPR bool operator==(optional<T> const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator!=(optional<T> const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator< (optional<T> const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator> (optional<T> const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator<=(optional<T> const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator>=(optional<T> const& lhs, optional<T> const& rhs);

// [X.Y.9] Comparisons with nullopt.
template <typename T> BKSGE_CONSTEXPR bool operator==(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator!=(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator< (optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator> (optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator<=(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator>=(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT;

template <typename T> BKSGE_CONSTEXPR bool operator==(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator!=(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator< (nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator> (nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator<=(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT;
template <typename T> BKSGE_CONSTEXPR bool operator>=(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT;

// [X.Y.10] Comparisons with value type.
template <typename T> BKSGE_CONSTEXPR bool operator==(optional<T> const& lhs, T const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator!=(optional<T> const& lhs, T const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator< (optional<T> const& lhs, T const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator> (optional<T> const& lhs, T const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator<=(optional<T> const& lhs, T const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator>=(optional<T> const& lhs, T const& rhs);

template <typename T> BKSGE_CONSTEXPR bool operator==(T const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator!=(T const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator< (T const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator> (T const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator<=(T const& lhs, optional<T> const& rhs);
template <typename T> BKSGE_CONSTEXPR bool operator>=(T const& lhs, optional<T> const& rhs);

// [X.Y.11]
template <typename T>
inline void
swap(optional<T>& lhs, optional<T>& rhs)
BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

}	// namespace bksge

#include <bksge/fnd/type_traits/remove_const.hpp>
#include <functional>	// hash

namespace std
{

template <typename T>
struct hash<bksge::optional<T>>
{
	std::size_t operator()(bksge::optional<T> const& opt) const BKSGE_NOEXCEPT
	{
        return static_cast<bool>(opt) ? hash<bksge::remove_const_t<T>>()(*opt) : 0;
	}
};

}	// namespace std

#include <bksge/fnd/optional/inl/optional_inl.hpp>

#endif

#endif // BKSGE_FND_OPTIONAL_OPTIONAL_HPP
