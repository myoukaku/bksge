/**
 *	@file	modulus.hpp
 *
 *	@brief	modulus 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MODULUS_HPP
#define BKSGE_FND_BIGINT_DETAIL_MODULUS_HPP

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
modulus(VectorType const& lhs, VectorType const& rhs)
{
	VectorType rem{};
	bigint_algo::div_mod(lhs, rhs, &rem);
	return rem;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MODULUS_HPP
