/**
 *	@file	begin.hpp
 *
 *	@brief	begin 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_BEGIN_HPP
#define BKSGE_FND_ITERATOR_BEGIN_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
begin(Container& c) -> decltype(c.begin())
{
	return c.begin();
}

template <typename Container>
inline BKSGE_CONSTEXPR auto
begin(Container const& c) -> decltype(c.begin())
{
	return c.begin();
}

template <typename T, bksge::size_t N>
inline BKSGE_CONSTEXPR T*
begin(T (&a)[N]) BKSGE_NOEXCEPT
{
	return a;
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_BEGIN_HPP
