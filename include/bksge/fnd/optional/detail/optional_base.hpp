/**
 *	@file	optional_base.hpp
 *
 *	@brief	optional_base の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP
#define BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>		// move
#include <initializer_list>

#if !defined(BKSGE_HAS_CXX11_UNRESTRICTED_UNIONS)
#  include <bksge/fnd/type_traits/aligned_storage.hpp>
#  include <bksge/fnd/type_traits/alignment_of.hpp>
#endif

namespace bksge
{

namespace detail
{

template <typename T, bool = bksge::is_trivially_destructible<T>::value>
class optional_base_impl
{
#include <bksge/fnd/optional/detail/optional_base_impl_common.hpp>
};

// T が TriviallyDestructible でないときのみ、デストラクタを提供する
template <typename T>
class optional_base_impl<T, false>
{
#include <bksge/fnd/optional/detail/optional_base_impl_common.hpp>
public:
	~optional_base_impl()
	{
		destroy();
	}
};

template <typename T>
class optional_base : public optional_base_impl<T>
{
private:
	using base = optional_base_impl<T>;

public:
	BKSGE_CONSTEXPR optional_base()
		: base{}
	{}

	BKSGE_CONSTEXPR optional_base(T const& t)
		: base{t}
	{}

	BKSGE_CONSTEXPR optional_base(T&& t)
		: base{std::move(t)}
	{}

	template <typename... Args>
	BKSGE_CONSTEXPR explicit
	optional_base(in_place_t t, Args&&... args)
		: base{t, bksge::forward<Args>(args)...}
	{}

	template <
		typename U,
		typename... Args
	>
	BKSGE_CONSTEXPR explicit
	optional_base(in_place_t t, std::initializer_list<U> il, Args&&... args)
		: base{t, il, bksge::forward<Args>(args)...}
	{}

	// Copy and move constructors.
	optional_base(optional_base const& other)
		: base{}
	{
		if (other.engaged())
		{
			this->construct(other.get());
		}
	}

	optional_base(optional_base&& other)
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<T>::value)
	{
		if (other.engaged())
		{
			this->construct(std::move(other.get()));
		}
	}

	// [X.Y.4.3] (partly) Assignment.
	optional_base& operator=(optional_base const& other)
	{
		if (this->engaged() && other.engaged())
		{
			this->get() = other.get();
		}
		else
		{
			if (other.engaged())
			{
				this->construct(other.get());
			}
			else
			{
				this->destroy();
			}
		}

		return *this;
	}

	optional_base& operator=(optional_base&& other)
		BKSGE_NOEXCEPT_IF(
			bksge::is_nothrow_move_constructible<T>::value &&
			bksge::is_nothrow_move_assignable<T>::value)
	{
		if (this->engaged() && other.engaged())
		{
			this->get() = std::move(other.get());
		}
		else
		{
			if (other.engaged())
			{
				this->construct(std::move(other.get()));
			}
			else
			{
				this->destroy();
			}
		}

		return *this;
	}

protected:
	BKSGE_CONSTEXPR bool engaged() const BKSGE_NOEXCEPT
	{
		return this->m_engaged;
	}
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_BASE_HPP
