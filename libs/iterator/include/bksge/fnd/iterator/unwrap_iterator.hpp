/**
 *	@file	unwrap_iterator.hpp
 *
 *	@brief	unwrap_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_UNWRAP_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_UNWRAP_ITERATOR_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Iter>
inline BKSGE_CONSTEXPR Iter
unwrap_iterator(Iter i) BKSGE_NOEXCEPT
{
    return i;
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_UNWRAP_ITERATOR_HPP
