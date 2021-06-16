/**
 *	@file	shift_right.hpp
 *
 *	@brief	shift_right 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_SHIFT_RIGHT_HPP
#define BKSGE_FND_BIGINT_DETAIL_SHIFT_RIGHT_HPP

#include <bksge/fnd/algorithm/shift_left.hpp>
#include <bksge/fnd/algorithm/fill.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

// bigint の文脈での右シフトは vector/array の文脈では左シフト

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::vector<T>&
shift_right(bksge::vector<T>& vec, bksge::size_t offset)
{
	auto const n = bksge::min(vec.size(), offset);
	bksge::shift_left(ranges::begin(vec), ranges::end(vec), n);
	vec.resize(vec.size() - n);
	return vec;
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR bksge::array<T, N>&
shift_right(bksge::array<T, N>& vec, bksge::size_t offset) noexcept
{
	auto const n = bksge::min(N, offset);
	bksge::shift_left(ranges::begin(vec), ranges::end(vec), n);
	bksge::fill(ranges::end(vec) - n, ranges::end(vec), T{0});
	return vec;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_SHIFT_RIGHT_HPP
