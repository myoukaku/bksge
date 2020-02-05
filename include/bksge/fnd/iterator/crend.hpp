/**
 *	@file	crend.hpp
 *
 *	@brief	crend 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CREND_HPP
#define BKSGE_FND_ITERATOR_CREND_HPP

#include <bksge/fnd/iterator/rend.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
crend(Container const& c)
BKSGE_NOEXCEPT_IF_EXPR(bksge::rend(c))
-> decltype(bksge::rend(c))
{
	return bksge::rend(c);
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CREND_HPP
