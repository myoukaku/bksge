/**
 *	@file	lo.hpp
 *
 *	@brief	lo 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_LO_HPP
#define BKSGE_FND_BIGINT_DETAIL_LO_HPP

#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <
	typename ElementType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR ElementType
lo(Integral value) noexcept
{
	return static_cast<ElementType>(value);
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_LO_HPP
