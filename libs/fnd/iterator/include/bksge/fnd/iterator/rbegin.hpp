﻿/**
 *	@file	rbegin.hpp
 *
 *	@brief	rbegin 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_RBEGIN_HPP
#define BKSGE_FND_ITERATOR_RBEGIN_HPP

#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
rbegin(Container& c) -> decltype(c.rbegin())
{
	return c.rbegin();
}

template <typename Container>
inline BKSGE_CONSTEXPR auto
rbegin(Container const& c) -> decltype(c.rbegin())
{
	return c.rbegin();
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR bksge::reverse_iterator<T*>
rbegin(T (&a)[N]) BKSGE_NOEXCEPT
{
	return bksge::reverse_iterator<T*>(a + N);
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_RBEGIN_HPP
