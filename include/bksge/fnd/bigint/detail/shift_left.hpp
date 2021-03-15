/**
 *	@file	shift_left.hpp
 *
 *	@brief	shift_left 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_SHIFT_LEFT_HPP
#define BKSGE_FND_BIGINT_DETAIL_SHIFT_LEFT_HPP

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
shift_left(bksge::vector<T> const& vec, bksge::size_t offset)
{
	auto const N = vec.size() + offset;
	bksge::vector<T> result(N);
	for (bksge::size_t i = offset; i < N; ++i)
	{
		result[i] = vec[i - offset];
	}
	return result;
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
shift_left(bksge::array<T, N> const& vec, bksge::size_t offset) noexcept
{
	bksge::array<T, N> result{};
	for (bksge::size_t i = offset; i < N; ++i)
	{
		result[i] = vec[i - offset];
	}
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_SHIFT_LEFT_HPP
