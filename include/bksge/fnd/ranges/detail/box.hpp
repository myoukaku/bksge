/**
 *	@file	box.hpp
 *
 *	@brief	box の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_BOX_HPP
#define BKSGE_FND_RANGES_DETAIL_BOX_HPP

#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/default_initializable.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/copyable.hpp>
#include <bksge/fnd/concepts/movable.hpp>
#include <bksge/fnd/concepts/semiregular.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/optional.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename T>
using boxable = bksge::conjunction<
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	bksge::bool_constant<bksge::copy_constructible<T>>,
#else
	bksge::copy_constructible<T>,
#endif
	bksge::is_object<T>
>;

template <
	typename T,
	bool = boxable<T>::value,
	bool = bksge::is_semiregular<T>::value
>
struct box;

template <typename T>
struct box<T, true, false> : bksge::optional<T>
{
	using bksge::optional<T>::optional;

	BKSGE_CONSTEXPR box()
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_default_constructible<T>::value)
		BKSGE_REQUIRES(bksge::default_initializable<T>)
		: bksge::optional<T>{bksge::in_place}
	{}

	BKSGE_CONSTEXPR box(box const&) = default;
	BKSGE_CONSTEXPR box(box&&) = default;

	using bksge::optional<T>::operator=;

	BKSGE_CXX14_CONSTEXPR box& operator=(box const& that)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_copy_constructible<T>::value)
		BKSGE_REQUIRES(!bksge::copyable<T>)
	{
		if ((bool)that)
		{
			this->emplace(*that);
		}
		else
		{
			this->reset();
		}

		return *this;
	}

	BKSGE_CXX14_CONSTEXPR box& operator=(box&& that)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<T>::value)
		BKSGE_REQUIRES(!bksge::movable<T>)
	{
		if ((bool)that)
		{
			this->emplace(bksge::move(*that));
		}
		else
		{
			this->reset();
		}

		return *this;
	}
};

template <typename T>
struct box<T, true, true>
{
private:
	BKSGE_NO_UNIQUE_ADDRESS T m_value = {};

public:
	BKSGE_CONSTEXPR box() = default;

	BKSGE_CONSTEXPR explicit
	box(T const& t)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_copy_constructible<T>::value)
		: m_value{t}
	{}

	BKSGE_CONSTEXPR explicit
	box(T&& t)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<T>::value)
		: m_value{bksge::move(t)}
	{}

	template <typename... Args>
	BKSGE_REQUIRES(bksge::constructible_from<T, Args...>)
	BKSGE_CONSTEXPR explicit
	box(bksge::in_place_t, Args&&... args)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, Args...>::value))
		: m_value{bksge::forward<Args>(args)...}
	{}

	BKSGE_CONSTEXPR bool has_value() const BKSGE_NOEXCEPT
	{
		return true;
	}

	BKSGE_CONSTEXPR T& operator*() BKSGE_NOEXCEPT
	{
		return m_value;
	}

	BKSGE_CONSTEXPR T const& operator*() const BKSGE_NOEXCEPT
	{
		return m_value;
	}

	BKSGE_CONSTEXPR T* operator->() BKSGE_NOEXCEPT
	{
		return &m_value;
	}

	BKSGE_CONSTEXPR T const* operator->() const BKSGE_NOEXCEPT
	{
		return &m_value;
	}
};

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_BOX_HPP
