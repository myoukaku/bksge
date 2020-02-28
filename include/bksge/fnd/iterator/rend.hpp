/**
 *	@file	rend.hpp
 *
 *	@brief	rend関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_REND_HPP
#define BKSGE_FND_ITERATOR_REND_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>	// reverse_iterator

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
rend(Container& c) -> decltype(c.rend())
{
	return c.rend();
}

template <typename Container>
inline BKSGE_CONSTEXPR auto
rend(Container const& c) -> decltype(c.rend())
{
	return c.rend();
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR std::reverse_iterator<T*>
rend(T (&a)[N]) BKSGE_NOEXCEPT
{
	return std::reverse_iterator<T*>(a);
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_REND_HPP
