/**
 *	@file	is_zero.hpp
 *
 *	@brief	is_zero 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_IS_ZERO_HPP
#define BKSGE_FND_BIGINT_DETAIL_IS_ZERO_HPP

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
inline BKSGE_CXX14_CONSTEXPR bool
is_zero(bksge::vector<T> const& value) noexcept
{
	return
		value.size() == 0 ||
		(value.size() == 1 && value[0] == 0);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bool
is_zero(bksge::array<T, N> const& value) noexcept
{
	for (std::size_t i = 0; i < N; ++i)
	{
		if (value[i] != 0)
		{
			return false;
		}
	}
	return true;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_IS_ZERO_HPP
