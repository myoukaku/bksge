/**
 *	@file	empty_view.hpp
 *
 *	@brief	empty_view の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_EMPTY_VIEW_HPP
#define BKSGE_FND_RANGES_VIEWS_EMPTY_VIEW_HPP

#include <bksge/fnd/ranges/views/view_interface.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include <bksge/fnd/ranges/detail/object.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace ranges
{

template <BKSGE_REQUIRES_PARAM(ranges::detail::object, T)>
class empty_view : public ranges::view_interface<empty_view<T>>
{
public:
	static BKSGE_CONSTEXPR T*          begin() BKSGE_NOEXCEPT { return nullptr; }
	static BKSGE_CONSTEXPR T*          end()   BKSGE_NOEXCEPT { return nullptr; }
	static BKSGE_CONSTEXPR T*          data()  BKSGE_NOEXCEPT { return nullptr; }
	static BKSGE_CONSTEXPR std::size_t size()  BKSGE_NOEXCEPT { return 0; }
	static BKSGE_CONSTEXPR bool        empty() BKSGE_NOEXCEPT { return true; }

	// 独自拡張
	BKSGE_CONSTEXPR empty_view<T> operator()() const
	{
		return empty_view<T>{};
	}
};

template <typename T>
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, empty_view<T>);

namespace views
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR empty_view<T> empty{};

#else

template <typename T>
BKSGE_CONSTEXPR empty_view<T> empty() { return empty_view<T>{}; }

#endif

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_EMPTY_VIEW_HPP
