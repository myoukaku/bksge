/**
 *	@file	crbegin.hpp
 *
 *	@brief	crbegin 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CRBEGIN_HPP
#define BKSGE_FND_ITERATOR_CRBEGIN_HPP

#include <bksge/fnd/iterator/rbegin.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
crbegin(Container const& c)
BKSGE_NOEXCEPT_IF_EXPR(bksge::rbegin(c))
-> decltype(bksge::rbegin(c))
{
	return bksge::rbegin(c);
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CRBEGIN_HPP
