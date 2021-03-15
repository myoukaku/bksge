/**
 *	@file	construct_from_size.hpp
 *
 *	@brief	construct_from_size 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_SIZE_HPP
#define BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_SIZE_HPP

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

namespace construct_from_size_detail
{

template <typename VectorType>
struct construct_from_size_impl;

template <typename T>
struct construct_from_size_impl<bksge::vector<T>>
{
	static BKSGE_CXX14_CONSTEXPR bksge::vector<T>
	invoke(bksge::size_t size)
	{
		return bksge::vector<T>(size);
	}
};

template <typename T, bksge::size_t N>
struct construct_from_size_impl<bksge::array<T, N>>
{
	static BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
	invoke(bksge::size_t)
	{
		return bksge::array<T, N>{};
	}
};

}	// namespace construct_from_size_detail

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR VectorType
construct_from_size(bksge::size_t size)
{
	return construct_from_size_detail::construct_from_size_impl<VectorType>::invoke(size);
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_SIZE_HPP
