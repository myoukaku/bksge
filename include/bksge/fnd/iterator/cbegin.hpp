/**
 *	@file	cbegin.hpp
 *
 *	@brief	cbegin 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CBEGIN_HPP
#define BKSGE_FND_ITERATOR_CBEGIN_HPP

#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
cbegin(Container const& c)
BKSGE_NOEXCEPT_IF_EXPR(bksge::begin(c))
-> decltype(bksge::begin(c))
{
	return bksge::begin(c);
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CBEGIN_HPP
