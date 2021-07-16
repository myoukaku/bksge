/**
 *	@file	get.hpp
 *
 *	@brief	get 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ARRAY_GET_HPP
#define BKSGE_FND_ARRAY_GET_HPP

#include <bksge/fnd/array/array.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

template <std::size_t I, typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR T&
get(array<T, N>& arr) BKSGE_NOEXCEPT
{
	static_assert(I < N, "array index is within bounds");
	return arr[I];
}

template <std::size_t I, typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR T&&
get(array<T, N>&& arr) BKSGE_NOEXCEPT
{
	static_assert(I < N, "array index is within bounds");
	return std::move(bksge::get<I>(arr));
}

template <std::size_t I, typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR T const&
get(array<T, N> const& arr) BKSGE_NOEXCEPT
{
	static_assert(I < N, "array index is within bounds");
	return arr[I];
}

template <std::size_t I, typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR T const&&
get(array<T, N> const&& arr) BKSGE_NOEXCEPT
{
	static_assert(I < N, "array index is within bounds");
	return std::move(bksge::get<I>(arr));
}

}	// namespace bksge

#endif // BKSGE_FND_ARRAY_GET_HPP
