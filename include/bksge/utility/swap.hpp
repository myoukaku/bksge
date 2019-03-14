/**
 *	@file	swap.hpp
 *
 *	@brief	swap 関数を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UTILITY_SWAP_HPP
#define BKSGE_UTILITY_SWAP_HPP

#include <bksge/config.hpp>
#include <cstddef>
#include <type_traits>
#include <utility>

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
	 typename std::enable_if<
	 std::is_move_constructible<T>::value &&
	 std::is_move_assignable<T>::value>::type* = nullptr)
BKSGE_NOEXCEPT_IF(
	std::is_nothrow_move_constructible<T>::value &&
	std::is_nothrow_move_assignable<T>::value)
{
	T temp = std::move(a);
	a = std::move(b);
	b = std::move(temp);
}

BKSGE_WARNING_POP()

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR
typename std::enable_if<bksge::is_swappable<T>::value>::type
swap(T(&a)[N], T(&b)[N])
BKSGE_NOEXCEPT_IF(bksge::is_nothrow_swappable<T>::value)
{
	for (std::size_t i = 0; i < N; ++i)
	{
		swap(a[i], b[i]);
	}
}

}	// namespace bksge

#include <bksge/type_traits/is_swappable.hpp>
#include <bksge/type_traits/is_nothrow_swappable.hpp>

#endif // BKSGE_UTILITY_SWAP_HPP
