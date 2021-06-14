/**
 *	@file	lg.hpp
 *
 *	@brief	lg の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_LG_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_LG_HPP

#include <bksge/fnd/bit/countl_zero.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>
#include <climits>	// CHAR_BIT

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T lg(T n)
{
	BKSGE_ASSERT(n > 0);
	using UT = bksge::make_unsigned_t<T>;
	return sizeof(T) * CHAR_BIT - 1 - bksge::countl_zero(static_cast<UT>(n));
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_LG_HPP
