/**
 *	@file	shift_left.hpp
 *
 *	@brief	shift_left 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_SHIFT_LEFT_HPP
#define BKSGE_FND_BIGINT_DETAIL_SHIFT_LEFT_HPP

#include <bksge/fnd/algorithm/shift_right.hpp>
#include <bksge/fnd/algorithm/fill_n.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

// bigint の文脈での左シフトは vector/array の文脈では右シフト

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::vector<T>&
shift_left(bksge::vector<T>& vec, std::size_t offset)
{
	vec.resize(vec.size() + offset);
	bksge::shift_right(ranges::begin(vec), ranges::end(vec), offset);
	bksge::fill_n(ranges::begin(vec), offset, T{0});
	return vec;
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bksge::array<T, N>&
shift_left(bksge::array<T, N>& vec, std::size_t offset)
{
	auto const n = bksge::min(N, offset);
	bksge::shift_right(ranges::begin(vec), ranges::end(vec), n);
	bksge::fill_n(ranges::begin(vec), n, T{0});
	return vec;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_SHIFT_LEFT_HPP
