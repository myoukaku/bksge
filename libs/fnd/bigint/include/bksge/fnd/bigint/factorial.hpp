/**
 *	@file	factorial.hpp
 *
 *	@brief	factorial の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_FACTORIAL_HPP
#define BKSGE_FND_BIGINT_FACTORIAL_HPP

#include <bksge/fnd/bigint/basic_bigint.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <bksge::size_t Bits, bool Signed>
inline BKSGE_CXX14_CONSTEXPR basic_bigint<Bits, Signed>
factorial(basic_bigint<Bits, Signed> n) BKSGE_NOEXCEPT
{
	basic_bigint<Bits, Signed> result{1};
	while (n > 1)
	{
		result *= n--;
	}
	return result;
}

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_FACTORIAL_HPP
