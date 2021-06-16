/**
 *	@file	to_array.hpp
 *
 *	@brief	to_array 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ARRAY_TO_ARRAY_HPP
#define BKSGE_FND_ARRAY_TO_ARRAY_HPP

#include <bksge/fnd/array/array.hpp>
#include <bksge/fnd/array/config.hpp>

#if defined(BKSGE_USE_STD_ARRAY) && defined(__cpp_lib_to_array) && (__cpp_lib_to_array >= 201907L)

#include <array>

namespace bksge
{

using std::to_array;

}	// namespace bksge

#else

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bksge::size_t N, bksge::size_t... I>
inline BKSGE_CONSTEXPR bksge::array<bksge::remove_cv_t<T>, N>
to_array_impl(T (&a)[N], bksge::index_sequence<I...>)
{
	return {{a[I]...}};
}

template <typename T, bksge::size_t N, bksge::size_t... I>
inline BKSGE_CONSTEXPR bksge::array<bksge::remove_cv_t<T>, N>
to_array_impl(T (&&a)[N], bksge::index_sequence<I...>)
{
	return {{bksge::move(a[I])...}};
}

}	// namespace detail

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR bksge::array<bksge::remove_cv_t<T>, N>
to_array(T (&a)[N])
BKSGE_NOEXCEPT_IF(bksge::is_nothrow_copy_constructible<T>::value)
{
	static_assert(!bksge::is_array<T>::value, "");
	static_assert(bksge::is_copy_constructible<T>::value, "");
	return bksge::detail::to_array_impl(a, bksge::make_index_sequence<N>{});
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR bksge::array<bksge::remove_cv_t<T>, N>
to_array(T (&&a)[N])
BKSGE_NOEXCEPT_IF(bksge::is_nothrow_move_constructible<T>::value)
{
	static_assert(!bksge::is_array<T>::value, "");
	static_assert(bksge::is_move_constructible<T>::value, "");
	return bksge::detail::to_array_impl(bksge::move(a), bksge::make_index_sequence<N>{});
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ARRAY_TO_ARRAY_HPP
