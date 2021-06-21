/**
 *	@file	infinity_bits.hpp
 *
 *	@brief	infinity_bits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_INFINITY_BITS_HPP
#define BKSGE_FND_BIGINT_INFINITY_BITS_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

BKSGE_INLINE_VAR BKSGE_CXX14_CONSTEXPR bksge::size_t
infinity_bits = std::numeric_limits<bksge::size_t>::max();

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_INFINITY_BITS_HPP
