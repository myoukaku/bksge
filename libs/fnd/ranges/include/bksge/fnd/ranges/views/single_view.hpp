/**
 *	@file	single_view.hpp
 *
 *	@brief	single_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_SINGLE_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_SINGLE_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/detail/box.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
template <bksge::copy_constructible T>
requires bksge::is_object<T>::value
#else
template <typename T,
	typename = bksge::enable_if_t<bksge::conjunction<
		bksge::copy_constructible<T>,
		bksge::is_object<T>
	>::value>
>
#endif
class single_view : public view_interface<single_view<T>>
{
public:
	BKSGE_CONSTEXPR single_view() = default;

	BKSGE_CONSTEXPR single_view(single_view const&) = default;
	BKSGE_CONSTEXPR single_view(single_view&&) = default;

	BKSGE_CXX14_CONSTEXPR single_view& operator=(single_view const&) = default;
	BKSGE_CXX14_CONSTEXPR single_view& operator=(single_view&&) = default;

	BKSGE_CONSTEXPR explicit single_view(T const& t)
		: m_value(t)
	{}

	BKSGE_CXX14_CONSTEXPR explicit single_view(T&& t)
		: m_value(std::move(t))
	{}

	template <typename... Args
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::constructible_from<T, Args...>::value
		>
#endif
	>
	BKSGE_REQUIRES(bksge::constructible_from<T, Args...>)
	BKSGE_CONSTEXPR explicit
	single_view(bksge::in_place_t, Args&&... args)
		: m_value{bksge::in_place, std::forward<Args>(args)...}
	{}

	BKSGE_CXX14_CONSTEXPR T* begin() BKSGE_NOEXCEPT
	{
		return data();
	}

	BKSGE_CONSTEXPR T const* begin() const BKSGE_NOEXCEPT
	{
		return data();
	}

	BKSGE_CXX14_CONSTEXPR T* end() BKSGE_NOEXCEPT
	{
		return data() + 1;
	}

	BKSGE_CONSTEXPR T const* end() const BKSGE_NOEXCEPT
	{
		return data() + 1;
	}

	static BKSGE_CONSTEXPR std::size_t size() BKSGE_NOEXCEPT
	{
		return 1;
	}

	BKSGE_CXX14_CONSTEXPR T* data() BKSGE_NOEXCEPT
	{
		return m_value.operator->();
	}

	BKSGE_CONSTEXPR T const* data() const BKSGE_NOEXCEPT
	{
		return m_value.operator->();
	}

private:
	BKSGE_NO_UNIQUE_ADDRESS detail::box<T> m_value;
};

namespace views
{

namespace detail
{

struct single_fn
{
	template <typename T>
	BKSGE_CONSTEXPR single_view<T> operator()(T&& t) const
	{
		return single_view<T>{std::forward<T>(t)};
	}
};

}	// namespace detail

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::single_fn single{};

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_SINGLE_VIEW_HPP
