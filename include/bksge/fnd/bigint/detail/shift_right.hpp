﻿/**
 *	@file	shift_right.hpp
 *
 *	@brief	shift_right 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_SHIFT_RIGHT_HPP
#define BKSGE_FND_BIGINT_DETAIL_SHIFT_RIGHT_HPP

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
shift_right(bksge::vector<T> const& vec, bksge::size_t offset)
{
	return bksge::vector<T>(vec.begin() + offset, vec.end());
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
shift_right(bksge::array<T, N> const& vec, bksge::size_t offset) noexcept
{
	bksge::array<T, N> result{};
	for (bksge::size_t i = offset; i < N; ++i)
	{
		result[i - offset] = vec[i];
	}
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_SHIFT_RIGHT_HPP
