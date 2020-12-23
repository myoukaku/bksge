/**
 *	@file	swap.hpp
 *
 *	@brief	swap 関数を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_SWAP_HPP
#define BKSGE_FND_UTILITY_SWAP_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename T>
struct is_swappable;
template <typename T>
struct is_nothrow_swappable;

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
swap(T& a, T& b,
	 bksge::enable_if_t<
	 bksge::is_move_constructible<T>::value &&
	 bksge::is_move_assignable<T>::value>* = nullptr)
BKSGE_NOEXCEPT_IF(
	bksge::is_nothrow_move_constructible<T>::value &&
	bksge::is_nothrow_move_assignable<T>::value)
{
	T temp = bksge::move(a);
	a = bksge::move(b);
	b = bksge::move(temp);
}

BKSGE_WARNING_POP()

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR
bksge::enable_if_t<bksge::is_swappable<T>::value>
swap(T(&a)[N], T(&b)[N])
BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
{
	for (bksge::size_t i = 0; i < N; ++i)
	{
		swap(a[i], b[i]);
	}
}

}	// namespace bksge

#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>

#endif // BKSGE_FND_UTILITY_SWAP_HPP
