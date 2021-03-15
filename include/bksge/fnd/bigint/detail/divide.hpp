/**
 *	@file	divide.hpp
 *
 *	@brief	divide 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_DIVIDE_HPP
#define BKSGE_FND_BIGINT_DETAIL_DIVIDE_HPP

#include <bksge/fnd/bigint/detail/div_mod.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR VectorType
divide(VectorType const& lhs, VectorType const& rhs)
{
	return bigint_algo::div_mod(lhs, rhs, static_cast<VectorType*>(nullptr));
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_DIVIDE_HPP
