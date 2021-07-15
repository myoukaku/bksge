/**
 *	@file	get_digits.hpp
 *
 *	@brief	get_digits 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_GET_DIGITS_HPP
#define BKSGE_FND_BIGINT_DETAIL_GET_DIGITS_HPP

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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR std::size_t
get_digits(bksge::vector<T> const& vec) noexcept
{
	return vec.size();
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR std::size_t
get_digits(bksge::array<T, N> const& vec) noexcept
{
	for (std::size_t i = N; i > 0; --i)
	{
		if (vec[i-1] != 0)
		{
			return i;
		}
	}
	return 1;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_GET_DIGITS_HPP
