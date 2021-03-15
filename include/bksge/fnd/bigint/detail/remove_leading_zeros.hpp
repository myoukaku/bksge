/**
 *	@file	remove_leading_zeros.hpp
 *
 *	@brief	remove_leading_zeros 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_REMOVE_LEADING_ZEROS_HPP
#define BKSGE_FND_BIGINT_DETAIL_REMOVE_LEADING_ZEROS_HPP

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
remove_leading_zeros(bksge::vector<T>& vec)
{
	while (vec.size() >= 2 && vec.back() == 0)
	{
		vec.pop_back();
	}
}

template <typename T, bksge::size_t N>
inline BKSGE_CXX14_CONSTEXPR void
remove_leading_zeros(bksge::array<T, N>&) noexcept
{}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_REMOVE_LEADING_ZEROS_HPP
