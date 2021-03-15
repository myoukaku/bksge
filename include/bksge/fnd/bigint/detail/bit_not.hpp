/**
 *	@file	bit_not.hpp
 *
 *	@brief	bit_not 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_BIT_NOT_HPP
#define BKSGE_FND_BIGINT_DETAIL_BIT_NOT_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::vector<T>
bit_not(bksge::vector<T> const& value)
{
	auto const N = value.size();
	bksge::vector<T> result(N);
	for (bksge::size_t i = 0; i < N; ++i)
	{
		result[i] = ~value[i];
	}
	return result;
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
bit_not(bksge::array<T, N> const& value) noexcept
{
	bksge::array<T, N> result{};
	for (bksge::size_t i = 0; i < N; ++i)
	{
		result[i] = ~value[i];
	}
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_BIT_NOT_HPP
