/**
 *	@file	optional_inl.hpp
 *
 *	@brief	optional の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_INL_OPTIONAL_INL_HPP
#define BKSGE_FND_OPTIONAL_INL_OPTIONAL_INL_HPP

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/optional/bad_optional_access.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>	// declval, move
#include <type_traits>
#include <initializer_list>

namespace bksge
{

template <typename T>
struct optional<T>::IsNothrowSwappable
{
	BKSGE_STATIC_CONSTEXPR bool value =
		std::is_nothrow_move_constructible<T>::value &&
		BKSGE_NOEXCEPT_EXPR(bksge::swap(std::declval<T&>(), std::declval<T&>()));
};

template <typename T>
struct optional<T>::IsNothrowMoveConstructible
{
	BKSGE_STATIC_CONSTEXPR bool value =
		std::is_nothrow_move_constructible<T>::value;
};

template <typename T>
struct optional<T>::IsNothrowMoveAssignable
{
	BKSGE_STATIC_CONSTEXPR bool value =
		std::is_nothrow_move_constructible<T>::value &&
		std::is_nothrow_move_assignable<T>::value;
};

template <typename T>
inline BKSGE_CONSTEXPR
optional<T>::optional()
	: base{}
{}

template <typename T>
inline BKSGE_CONSTEXPR
optional<T>::optional(nullopt_t) BKSGE_NOEXCEPT
	: base{}
{}

template <typename T>
inline BKSGE_CONSTEXPR
optional<T>::optional(T const& t)
	: base{t}
{}

template <typename T>
inline BKSGE_CONSTEXPR
optional<T>::optional(T&& t)
	: base{std::move(t)}
{}

template <typename T>
template <typename... Args>
inline BKSGE_CONSTEXPR
optional<T>::optional(in_place_t t, Args&&... args)
	: base{t, bksge::forward<Args>(args)...}
{}

template <typename T>
template <typename U, typename... Args, typename>
inline BKSGE_CONSTEXPR
optional<T>::optional(in_place_t t, std::initializer_list<U> il, Args&&... args)
	: base{t, il, bksge::forward<Args>(args)...}
{}

#if defined(_MSC_VER) && (_MSC_VER <= 1900)

template <typename T>
inline
optional<T>::optional(optional const& other)
	: base{static_cast<base const&>(other)}
{}

template <typename T>
inline
optional<T>::optional(optional&& other)
	BKSGE_NOEXCEPT_IF(IsNothrowMoveConstructible::value)
	: base{static_cast<base&&>(other)}
{}

#endif

template <typename T>
inline auto
optional<T>::operator=(nullopt_t) BKSGE_NOEXCEPT
-> optional&
{
	this->destroy();
	return *this;
}

#if defined(_MSC_VER) && (_MSC_VER <= 1900)

template <typename T>
inline auto
optional<T>::operator=(optional const& other)
-> optional&
{
	base::operator=(static_cast<base const&>(other));
	return *this;
}

template <typename T>
inline auto
optional<T>::operator=(optional&& other)
	BKSGE_NOEXCEPT_IF(IsNothrowMoveAssignable::value)
-> optional&
{
	base::operator=(static_cast<base&&>(other));
	return *this;
}

#endif

template <typename T>
template <typename U, typename>
inline auto
optional<T>::operator=(U&& u)
-> optional&
{
	static_assert(
		std::is_constructible<T, U>::value &&
		std::is_assignable<T&, U>::value,
		"Cannot assign to value type from argument");

	if (this->engaged())
	{
		this->get() = bksge::forward<U>(u);
	}
	else
	{
		this->construct(bksge::forward<U>(u));
	}

	return *this;
}

template <typename T>
template <typename... Args>
inline void
optional<T>::emplace(Args&&... args)
{
	static_assert(
		std::is_constructible<T, Args&&...>::value,
		"Cannot emplace value type from arguments");

	this->destroy();
	this->construct(bksge::forward<Args>(args)...);
}

template <typename T>
template <typename U, typename... Args, typename>
inline void
optional<T>::emplace(std::initializer_list<U> il, Args&&... args)
{
	this->destroy();
	this->construct(il, bksge::forward<Args>(args)...);
}

template <typename T>
inline void
optional<T>::swap(optional& other)
BKSGE_NOEXCEPT_IF(IsNothrowSwappable::value)
{
	using bksge::swap;

	if (this->engaged() && other.engaged())
	{
		swap(this->get(), other.get());
	}
	else if (this->engaged())
	{
		other.construct(std::move(this->get()));
		this->destroy();
	}
	else if (other.engaged())
	{
		this->construct(std::move(other.get()));
		other.destroy();
	}
}

template <typename T>
inline BKSGE_CONSTEXPR T const*
optional<T>::operator->() const
{
	return bksge::addressof(this->get());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T*
optional<T>::operator->()
{
	return bksge::addressof(this->get());
}

#if defined(BKSGE_HAS_CXX11_REF_QUALIFIERS)

template <typename T>
inline BKSGE_CONSTEXPR T const&
optional<T>::operator*() const&
{
	return this->get();
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T&
optional<T>::operator*() &
{
	return this->get();
}

template <typename T>
inline BKSGE_CONSTEXPR T const&&
optional<T>::operator*() const&&
{
	return std::move(this->get());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T&&
optional<T>::operator*() &&
{
	return std::move(this->get());
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T const&
optional<T>::operator*() const
{
	return this->get();
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T&
optional<T>::operator*()
{
	return this->get();
}

#endif

template <typename T>
inline BKSGE_CONSTEXPR
optional<T>::operator bool() const BKSGE_NOEXCEPT
{
	return this->engaged();
}

#if defined(BKSGE_HAS_CXX11_REF_QUALIFIERS)

template <typename T>
inline BKSGE_CONSTEXPR T const&
optional<T>::value() const&
{
	return engaged_check(), this->get();
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T&
optional<T>::value() &
{
	return engaged_check(), this->get();
}

template <typename T>
inline BKSGE_CONSTEXPR T const&&
optional<T>::value() const&&
{
	return engaged_check(), std::move(this->get());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T&&
optional<T>::value() &&
{
	return engaged_check(), std::move(this->get());
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T const&
optional<T>::value() const
{
	return engaged_check(), this->get();
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T&
optional<T>::value()
{
	return engaged_check(), this->get();
}

#endif

#if defined(BKSGE_HAS_CXX11_REF_QUALIFIERS)

template <typename T>
template <typename U>
inline BKSGE_CONSTEXPR T
optional<T>::value_or(U&& u) const&
{
	static_assert(
		std::is_copy_constructible<T>::value &&
		std::is_convertible<U&&, T>::value,
		"Cannot return value");

	return this->engaged() ?
		this->get() :
		static_cast<T>(bksge::forward<U>(u));
}

template <typename T>
template <typename U>
inline BKSGE_CXX14_CONSTEXPR T
optional<T>::value_or(U&& u) &&
{
	static_assert(
		std::is_move_constructible<T>::value &&
		std::is_convertible<U&&, T>::value,
		"Cannot return value");

	return this->engaged() ?
		std::move(this->get()) :
		static_cast<T>(bksge::forward<U>(u));
}

#else

template <typename T>
template <typename U>
inline BKSGE_CONSTEXPR T
optional<T>::value_or(U&& u) const
{
	static_assert(
		std::is_copy_constructible<T>::value &&
		std::is_convertible<U&&, T>::value,
		"Cannot return value");

	return this->engaged() ?
		this->get() :
		static_cast<T>(bksge::forward<U>(u));
}

#endif

template <typename T>
inline BKSGE_CONSTEXPR bool
optional<T>::engaged_check() const
{
	return this->engaged() ? true :
		(bksge::throw_bad_optional_access(), false);
}

// [X.Y.8] Comparisons between optional values.
template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(optional<T> const& lhs, optional<T> const& rhs)
{
	return static_cast<bool>(lhs) == static_cast<bool>(rhs) &&
		(!lhs || *lhs == *rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(optional<T> const& lhs, optional<T> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<(optional<T> const& lhs, optional<T> const& rhs)
{
	return static_cast<bool>(rhs) && (!lhs || *lhs < *rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>(optional<T> const& lhs, optional<T> const& rhs)
{
	return rhs < lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<=(optional<T> const& lhs, optional<T> const& rhs)
{
	return !(rhs < lhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>=(optional<T> const& lhs, optional<T> const& rhs)
{
	return !(lhs < rhs);
}

// [X.Y.9] Comparisons with nullopt.
template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(optional<T> const& lhs, nullopt_t) BKSGE_NOEXCEPT
{
	return !lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<(optional<T> const& /*lhs*/, nullopt_t) BKSGE_NOEXCEPT
{
	return false;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT
{
	return rhs < lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<=(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT
{
	return !(rhs < lhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>=(optional<T> const& lhs, nullopt_t rhs) BKSGE_NOEXCEPT
{
	return !(lhs < rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(nullopt_t /*lhs*/, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return !rhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<(nullopt_t, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return static_cast<bool>(rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return rhs < lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<=(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return !(rhs < lhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>=(nullopt_t lhs, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs < rhs);
}

// [X.Y.10] Comparisons with value type.
template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(optional<T> const& lhs, T const& rhs)
{
	return lhs && *lhs == rhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(optional<T> const& lhs, T const& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<(optional<T> const& lhs, T const& rhs)
{
	return !lhs || *lhs < rhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>(optional<T> const& lhs, T const& rhs)
{
	return rhs < lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<=(optional<T> const& lhs, T const& rhs)
{
	return !(rhs < lhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>=(optional<T> const& lhs, T const& rhs)
{
	return !(lhs < rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator==(T const& lhs, optional<T> const& rhs)
{
	return rhs && lhs == *rhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator!=(T const& lhs, optional<T> const& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<(T const& lhs, optional<T> const& rhs)
{
	return rhs && lhs < *rhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>(T const& lhs, optional<T> const& rhs)
{
	return rhs < lhs;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator<=(T const& lhs, optional<T> const& rhs)
{
	return !(rhs < lhs);
}

template <typename T>
inline BKSGE_CONSTEXPR bool
operator>=(T const& lhs, optional<T> const& rhs)
{
	return !(lhs < rhs);
}

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_INL_OPTIONAL_INL_HPP
