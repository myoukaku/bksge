/**
 *	@file	default_sentinel.hpp
 *
 *	@brief	default_sentinel の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_DEFAULT_SENTINEL_HPP
#define BKSGE_FND_ITERATOR_DEFAULT_SENTINEL_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

struct default_sentinel_t {};

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
default_sentinel_t default_sentinel{};

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_DEFAULT_SENTINEL_HPP
