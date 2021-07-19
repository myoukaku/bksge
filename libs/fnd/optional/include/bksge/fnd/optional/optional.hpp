/**
 *	@file	optional.hpp
 *
 *	@brief	optional の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_OPTIONAL_HPP
#define BKSGE_FND_OPTIONAL_OPTIONAL_HPP

#include <bksge/fnd/optional/config.hpp>

#if defined(BKSGE_USE_STD_OPTIONAL)

#include <optional>

namespace bksge
{

using std::optional;

}	// namespace bksge

#else

#include <bksge/fnd/optional/detail/optional_base.hpp>
#include <bksge/fnd/optional/detail/optional_relop_t.hpp>
#include <bksge/fnd/optional/bad_optional_access.hpp>
#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/detail/enable_copy_move.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_scalar.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>
#include <initializer_list>
#include <utility>

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
#include <bksge/fnd/compare/concepts/three_way_comparable_with.hpp>
#include <bksge/fnd/compare/compare_three_way_result.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#endif

namespace bksge
{

/**
  * @brief Class template for optional values.
  */
template <typename T>
class optional
	: private bksge::detail::optional_base<T>
	, private bksge::detail::enable_copy_move<
		bksge::conjunction<bksge::is_copy_constructible<T>>::value,
		bksge::conjunction<bksge::is_copy_constructible<T>, bksge::is_copy_assignable<T>>::value,
		bksge::conjunction<bksge::is_move_constructible<T>>::value,
		bksge::conjunction<bksge::is_move_constructible<T>, bksge::is_move_assignable<T>>::value,
		optional<T>
	>
{
	static_assert(!bksge::is_same<bksge::remove_cv_t<T>, bksge::nullopt_t>::value, "");
	static_assert(!bksge::is_same<bksge::remove_cv_t<T>, bksge::in_place_t>::value, "");
	static_assert(!bksge::is_reference<T>::value, "");

private:
	using base = bksge::detail::optional_base<T>;

	// SFINAE helpers
	template <typename U>
	using not_self = bksge::negation<bksge::is_same<optional, bksge::remove_cvref_t<U>>>;

	template <typename U>
	using not_tag = bksge::negation<bksge::is_same<bksge::in_place_t, bksge::remove_cvref_t<U>>>;

	template <typename U>
	using not_converts_from_optional =
		bksge::negation<bksge::disjunction<
			bksge::is_constructible<T, optional<U> const&>,
			bksge::is_constructible<T, optional<U>&>,
			bksge::is_constructible<T, optional<U> const&&>,
			bksge::is_constructible<T, optional<U>&&>,
			bksge::is_convertible<optional<U> const&, T>,
			bksge::is_convertible<optional<U>&, T>,
			bksge::is_convertible<optional<U> const&&, T>,
			bksge::is_convertible<optional<U>&&, T>
		>>;

	template <typename U>
	using not_assigns_from_optional =
		bksge::negation<bksge::disjunction<
			bksge::is_assignable<T&, optional<U> const&>,
			bksge::is_assignable<T&, optional<U>&>,
			bksge::is_assignable<T&, optional<U> const&&>,
			bksge::is_assignable<T&, optional<U>&&>
		>>;

public:
	using value_type = T;

	BKSGE_CONSTEXPR optional() BKSGE_NOEXCEPT {}

	BKSGE_CONSTEXPR optional(bksge::nullopt_t) BKSGE_NOEXCEPT {}

	// Converting constructors for engaged optionals.
	template <typename U = T,
		bksge::enable_if_t<bksge::conjunction<
			not_self<U>,
			not_tag<U>,
			bksge::is_constructible<T, U>,
			bksge::is_convertible<U, T>
		>::value>* = nullptr
	>
	BKSGE_CONSTEXPR
	optional(U&& t)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, U>::value))
		: base(bksge::in_place, std::forward<U>(t)) {}

	template <typename U = T,
		bksge::enable_if_t<bksge::conjunction<
			not_self<U>,
			not_tag<U>,
			bksge::is_constructible<T, U>,
			bksge::negation<bksge::is_convertible<U, T>>
		>::value>* = nullptr
	>
	explicit BKSGE_CONSTEXPR
	optional(U&& t)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, U>::value))
		: base(bksge::in_place, std::forward<U>(t)) {}

	template <typename U,
		bksge::enable_if_t<bksge::conjunction<
			bksge::negation<bksge::is_same<T, U>>,
			bksge::is_constructible<T, U const&>,
			bksge::is_convertible<U const&, T>,
			not_converts_from_optional<U>
		>::value>* = nullptr
	>
	BKSGE_CXX14_CONSTEXPR
	optional(optional<U> const& t)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, U const&>::value))
	{
		if (t)
		{
			emplace(*t);
		}
	}

	template <typename U,
		bksge::enable_if_t<bksge::conjunction<
			bksge::negation<bksge::is_same<T, U>>,
			bksge::is_constructible<T, U const&>,
			bksge::negation<bksge::is_convertible<U const&, T>>,
			not_converts_from_optional<U>
		>::value>* = nullptr
	>
	explicit BKSGE_CXX14_CONSTEXPR
	optional(optional<U> const& t)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, U const&>::value))
	{
		if (t)
		{
			emplace(*t);
		}
	}

	template <typename U,
		bksge::enable_if_t<bksge::conjunction<
			bksge::negation<bksge::is_same<T, U>>,
			bksge::is_constructible<T, U>,
			bksge::is_convertible<U, T>,
			not_converts_from_optional<U>
		>::value>* = nullptr
	>
	BKSGE_CXX14_CONSTEXPR
	optional(optional<U>&& t)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, U>::value))
	{
		if (t)
		{
			emplace(std::move(*t));
		}
	}

	template <typename U,
		bksge::enable_if_t<bksge::conjunction<
			bksge::negation<bksge::is_same<T, U>>,
			bksge::is_constructible<T, U>,
			bksge::negation<bksge::is_convertible<U, T>>,
			not_converts_from_optional<U>
		>::value>* = nullptr
	>
	explicit BKSGE_CXX14_CONSTEXPR
	optional(optional<U>&& t)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, U>::value))
	{
		if (t)
		{
			emplace(std::move(*t));
		}
	}

	template <typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>>
	explicit BKSGE_CONSTEXPR
	optional(bksge::in_place_t, Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<T, Args...>::value))
		: base(bksge::in_place, std::forward<Args>(args)...) {}

	template <typename U, typename... Args,
		typename = bksge::enable_if_t<bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value>>
	explicit BKSGE_CONSTEXPR
	optional(bksge::in_place_t, std::initializer_list<U> il, Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value))
		: base(bksge::in_place, il, std::forward<Args>(args)...) {}

	// Assignment operators.
	optional& operator=(bksge::nullopt_t) BKSGE_NOEXCEPT
	{
		this->reset_impl();
		return *this;
	}

	template <typename U = T>
	bksge::enable_if_t<
		bksge::conjunction<
			not_self<U>,
			bksge::negation<
				bksge::conjunction<
					bksge::is_scalar<T>,
					bksge::is_same<T, bksge::decay_t<U>>
				>
			>,
			bksge::is_constructible<T, U>,
			bksge::is_assignable<T&, U>
		>::value,
		optional&
	>
	operator=(U&& u)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T, U>,
			bksge::is_nothrow_assignable<T&, U>>::value))
	{
		if (this->is_engaged())
		{
			this->get() = std::forward<U>(u);
		}
		else
		{
			this->construct(std::forward<U>(u));
		}

		return *this;
	}

	template <typename U>
	bksge::enable_if_t<
		bksge::conjunction<
			bksge::negation<bksge::is_same<T, U>>,
			bksge::is_constructible<T, U const&>,
			bksge::is_assignable<T&, U>,
			not_converts_from_optional<U>,
			not_assigns_from_optional<U>
		>::value,
		optional&
	>
	operator=(optional<U> const& u)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T, U const&>,
			bksge::is_nothrow_assignable<T&, U const&>>::value))
	{
		if (u)
		{
			if (this->is_engaged())
			{
				this->get() = *u;
			}
			else
			{
				this->construct(*u);
			}
		}
		else
		{
			this->reset_impl();
		}
		return *this;
	}

	template <typename U>
	bksge::enable_if_t<
		bksge::conjunction<
			bksge::negation<bksge::is_same<T, U>>,
			bksge::is_constructible<T, U>,
			bksge::is_assignable<T&, U>,
			not_converts_from_optional<U>,
			not_assigns_from_optional<U>
		>::value,
		optional&
	>
	operator=(optional<U>&& u)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T, U>,
			bksge::is_nothrow_assignable<T&, U>>::value))
	{
		if (u)
		{
			if (this->is_engaged())
			{
				this->get() = std::move(*u);
			}
			else
			{
				this->construct(std::move(*u));
			}
		}
		else
		{
			this->reset_impl();
		}

		return *this;
	}

	template <typename... Args>
	bksge::enable_if_t<bksge::is_constructible<T, Args...>::value, T&>
	emplace(Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<T, Args...>::value))
	{
		this->reset_impl();
		this->construct(std::forward<Args>(args)...);
		return this->get();
	}

	template <typename U, typename... Args>
	bksge::enable_if_t<bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value, T&>
	emplace(std::initializer_list<U> il, Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value))
	{
		this->reset_impl();
		this->construct(il, std::forward<Args>(args)...);
		return this->get();
	}

	// Destructor is implicit, implemented in optional_base.

	// Swap.
	void swap(optional& other)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_move_constructible<T>,
			bksge::is_nothrow_swappable<T>>::value))
	{
		using bksge::swap;

		if (this->is_engaged() && other.is_engaged())
		{
			swap(this->get(), other.get());
		}
		else if (this->is_engaged())
		{
			other.construct(std::move(this->get()));
			this->destruct();
		}
		else if (other.is_engaged())
		{
			this->construct(std::move(other.get()));
			other.destruct();
		}
	}

	// Observers.
	BKSGE_CONSTEXPR T const*
	operator->() const BKSGE_NOEXCEPT
	{
		return bksge::addressof(this->get());
	}

	BKSGE_CXX14_CONSTEXPR T*
	operator->() BKSGE_NOEXCEPT
	{
		return bksge::addressof(this->get());
	}

	BKSGE_CONSTEXPR T const&
	operator*() const& BKSGE_NOEXCEPT
	{
		return this->get();
	}

	BKSGE_CXX14_CONSTEXPR T&
	operator*() & BKSGE_NOEXCEPT
	{
		return this->get();
	}

	BKSGE_CXX14_CONSTEXPR T const&&
	operator*() const&& BKSGE_NOEXCEPT
	{
		return std::move(this->get());
	}

	BKSGE_CXX14_CONSTEXPR T&&
	operator*() && BKSGE_NOEXCEPT
	{
		return std::move(this->get());
	}

	BKSGE_CONSTEXPR explicit operator bool() const BKSGE_NOEXCEPT
	{
		return this->is_engaged();
	}

	BKSGE_CONSTEXPR bool has_value() const BKSGE_NOEXCEPT
	{
		return this->is_engaged();
	}

	BKSGE_WARNING_PUSH();
	BKSGE_WARNING_DISABLE_MSVC(4702);	// unreachable code
	BKSGE_CONSTEXPR T const& value() const&
	{
		return this->is_engaged()
			? this->get()
			: (throw_bad_optional_access(), this->get());
	}
	BKSGE_WARNING_POP();

	BKSGE_CXX14_CONSTEXPR T& value() &
	{
		return this->is_engaged()
			? this->get()
			: (throw_bad_optional_access(), this->get());
	}

	BKSGE_CXX14_CONSTEXPR T const&& value() const&&
	{
		return this->is_engaged()
			? std::move(this->get())
			: (throw_bad_optional_access(), std::move(this->get()));
	}

	BKSGE_CXX14_CONSTEXPR T&& value() &&
	{
		return this->is_engaged()
			? std::move(this->get())
			: (throw_bad_optional_access(), std::move(this->get()));
	}

	template <typename U>
	BKSGE_CONSTEXPR T value_or(U&& u) const&
	{
		static_assert(bksge::is_copy_constructible<T>::value, "");
		static_assert(bksge::is_convertible<U&&, T>::value, "");

		return this->is_engaged() ? this->get() : static_cast<T>(std::forward<U>(u));
	}

	template <typename U>
	BKSGE_CXX14_CONSTEXPR T value_or(U&& u) &&
	{
		static_assert(bksge::is_move_constructible<T>::value, "");
		static_assert(bksge::is_convertible<U&&, T>::value, "");

		return this->is_engaged() ? std::move(this->get()) : static_cast<T>(std::forward<U>(u));
	}

	void reset() BKSGE_NOEXCEPT { this->reset_impl(); }
};


// Comparisons between optional values.
template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator==(optional<T> const& lhs, optional<U> const& rhs)
-> detail::optional_eq_t<T, U>
{
	return static_cast<bool>(lhs) == static_cast<bool>(rhs) && (!lhs || *lhs == *rhs);
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator!=(optional<T> const& lhs, optional<U> const& rhs)
-> detail::optional_ne_t<T, U>
{
	return static_cast<bool>(lhs) != static_cast<bool>(rhs) || (static_cast<bool>(lhs) && *lhs != *rhs);
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator<(optional<T> const& lhs, optional<U> const& rhs)
-> detail::optional_lt_t<T, U>
{
	return static_cast<bool>(rhs) && (!lhs || *lhs < *rhs);
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator>(optional<T> const& lhs, optional<U> const& rhs)
-> detail::optional_gt_t<T, U>
{
	return static_cast<bool>(lhs) && (!rhs || *lhs > *rhs);
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator<=(optional<T> const& lhs, optional<U> const& rhs)
-> detail::optional_le_t<T, U>
{
	return !lhs || (static_cast<bool>(rhs) && *lhs <= *rhs);
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator>=(optional<T> const& lhs, optional<U> const& rhs)
-> detail::optional_ge_t<T, U>
{
	return !rhs || (static_cast<bool>(lhs) && *lhs >= *rhs);
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, bksge::three_way_comparable_with<T> U>
BKSGE_CONSTEXPR bksge::compare_three_way_result_t<T, U>
operator<=>(optional<T> const& lhs, optional<U> const& rhs)
{
	return lhs && rhs ? *lhs <=> *rhs : bool(lhs) <=> bool(rhs);
}
#endif

// Comparisons with nullopt.
template <typename T>
BKSGE_CONSTEXPR bool
operator==(optional<T> const& lhs, bksge::nullopt_t) BKSGE_NOEXCEPT
{
	return !lhs;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T>
BKSGE_CONSTEXPR bksge::strong_ordering
operator<=>(optional<T> const& lhs, bksge::nullopt_t) BKSGE_NOEXCEPT
{
	return bool(lhs) <=> false;
}
#else
template <typename T>
BKSGE_CONSTEXPR bool
operator==(bksge::nullopt_t, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return !rhs;
}

template <typename T>
BKSGE_CONSTEXPR bool
operator!=(optional<T> const& lhs, bksge::nullopt_t) BKSGE_NOEXCEPT
{
	return static_cast<bool>(lhs);
}

template <typename T>
BKSGE_CONSTEXPR bool
operator!=(bksge::nullopt_t, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return static_cast<bool>(rhs);
}

template <typename T>
BKSGE_CONSTEXPR bool
operator<(optional<T> const& /*lhs*/, bksge::nullopt_t) BKSGE_NOEXCEPT
{
	return false;
}

template <typename T>
BKSGE_CONSTEXPR bool
operator<(bksge::nullopt_t, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return static_cast<bool>(rhs);
}

template <typename T>
BKSGE_CONSTEXPR bool
operator>(optional<T> const& lhs, bksge::nullopt_t) BKSGE_NOEXCEPT
{
	return static_cast<bool>(lhs);
}

template <typename T>
BKSGE_CONSTEXPR bool
operator>(bksge::nullopt_t, optional<T> const& /*rhs*/) BKSGE_NOEXCEPT
{
	return false;
}

template <typename T>
BKSGE_CONSTEXPR bool
operator<=(optional<T> const& lhs, bksge::nullopt_t) BKSGE_NOEXCEPT
{
	return !lhs;
}

template <typename T>
BKSGE_CONSTEXPR bool
operator<=(bksge::nullopt_t, optional<T> const& /*rhs*/) BKSGE_NOEXCEPT
{
	return true;
}

template <typename T>
BKSGE_CONSTEXPR bool
operator>=(optional<T> const& /*lhs*/, bksge::nullopt_t) BKSGE_NOEXCEPT
{
	return true;
}

template <typename T>
BKSGE_CONSTEXPR bool
operator>=(bksge::nullopt_t, optional<T> const& rhs) BKSGE_NOEXCEPT
{
	return !rhs;
}
#endif // three-way-comparison

// Comparisons with value type.
template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator==(optional<T> const& lhs, U const& rhs)
-> detail::optional_eq_t<T, U>
{
	return lhs && *lhs == rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator==(U const& lhs, optional<T> const& rhs)
-> detail::optional_eq_t<U, T>
{
	return rhs && lhs == *rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator!=(optional<T> const& lhs, U const& rhs)
-> detail::optional_ne_t<T, U>
{
	return !lhs || *lhs != rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator!=(U const& lhs, optional<T> const& rhs)
-> detail::optional_ne_t<U, T>
{
	return !rhs || lhs != *rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator<(optional<T> const& lhs, U const& rhs)
-> detail::optional_lt_t<T, U>
{
	return !lhs || *lhs < rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator<(U const& lhs, optional<T> const& rhs)
-> detail::optional_lt_t<U, T>
{
	return rhs && lhs < *rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator>(optional<T> const& lhs, U const& rhs)
-> detail::optional_gt_t<T, U>
{
	return lhs && *lhs > rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator>(U const& lhs, optional<T> const& rhs)
-> detail::optional_gt_t<U, T>
{
	return !rhs || lhs > *rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator<=(optional<T> const& lhs, U const& rhs)
-> detail::optional_le_t<T, U>
{
	return !lhs || *lhs <= rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator<=(U const& lhs, optional<T> const& rhs)
-> detail::optional_le_t<U, T>
{
	return rhs && lhs <= *rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator>=(optional<T> const& lhs, U const& rhs)
-> detail::optional_ge_t<T, U>
{
	return lhs && *lhs >= rhs;
}

template <typename T, typename U>
BKSGE_CONSTEXPR auto
operator>=(U const& lhs, optional<T> const& rhs)
-> detail::optional_ge_t<U, T>
{
	return !rhs || lhs >= *rhs;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U>
BKSGE_CONSTEXPR bksge::compare_three_way_result_t<T, U>
operator<=>(optional<T> const& lhs, U const& rhs)
{
	return bool(lhs) ? *lhs <=> rhs : bksge::strong_ordering::less;
}
#endif

template <typename T,
	bksge::enable_if_t<bksge::conjunction<
		bksge::is_move_constructible<T>,
		bksge::is_swappable<T>
	>::value>* = nullptr
>
inline void
swap(optional<T>& lhs, optional<T>& rhs)
	BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

template <typename T,
	bksge::enable_if_t<!bksge::conjunction<
		bksge::is_move_constructible<T>,
		bksge::is_swappable<T>
	>::value>* = nullptr
>
void swap(optional<T>&, optional<T>&) = delete;


#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T>
optional(T) -> optional<T>;

#endif

}	// namespace bksge

#endif

#include <bksge/fnd/functional/config.hpp>

#if !defined(BKSGE_USE_STD_OPTIONAL) || !defined(BKSGE_USE_STD_HASH)

#include <bksge/fnd/optional/detail/optional_hash_call_base.hpp>

namespace BKSGE_HASH_NAMESPACE
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4624);	// destructor was implicitly defined as deleted

template <typename T>
struct hash<bksge::optional<T>>
	: public bksge::detail::optional_hash_call_base<T>
{};

BKSGE_WARNING_POP();

}	// namespace BKSGE_HASH_NAMESPACE

#endif

#endif // BKSGE_FND_OPTIONAL_OPTIONAL_HPP
