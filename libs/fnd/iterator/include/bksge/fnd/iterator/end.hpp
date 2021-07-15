/**
 *	@file	end.hpp
 *
 *	@brief	end 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_END_HPP
#define BKSGE_FND_ITERATOR_END_HPP

#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <typename Container>
inline BKSGE_CONSTEXPR auto
end(Container& c) -> decltype(c.end())
{
	return c.end();
}

template <typename Container>
inline BKSGE_CONSTEXPR auto
end(Container const& c) -> decltype(c.end())
{
	return c.end();
}

template <typename T, std::size_t N>
inline BKSGE_CONSTEXPR T*
end(T (&a)[N]) BKSGE_NOEXCEPT
{
	return a + N;
}

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_END_HPP
