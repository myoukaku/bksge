/**
 *	@file	cend.hpp
 *
 *	@brief	cend 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CEND_HPP
#define BKSGE_FND_ITERATOR_CEND_HPP

#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
cend(Container const& c)
BKSGE_NOEXCEPT_IF_EXPR(bksge::end(c))
-> decltype(bksge::end(c))
{
	return bksge::end(c);
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CEND_HPP
