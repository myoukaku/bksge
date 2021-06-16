/**
 *	@file	get_sign.hpp
 *
 *	@brief	get_sign 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_GET_SIGN_HPP
#define BKSGE_FND_BIGINT_DETAIL_GET_SIGN_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
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
inline BKSGE_CXX14_CONSTEXPR int
get_sign(bksge::vector<T> const&) noexcept
{
	return 1;
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR int
get_sign(bksge::array<T, N> const& vec) noexcept
{
	T const sign_bit = (1 << (bksge::bitsof<T>() - 1));
	return ((vec[N - 1] & sign_bit) == 0) ? 1 : -1;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_GET_SIGN_HPP
