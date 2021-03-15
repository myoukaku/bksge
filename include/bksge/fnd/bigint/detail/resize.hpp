/**
 *	@file	resize.hpp
 *
 *	@brief	resize 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_RESIZE_HPP
#define BKSGE_FND_BIGINT_DETAIL_RESIZE_HPP

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
inline BKSGE_CXX14_CONSTEXPR void
resize(bksge::vector<T>& vec, bksge::size_t n)
{
	vec.resize(n);
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR void
resize(bksge::array<T, N>&, bksge::size_t) noexcept
{}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_RESIZE_HPP
