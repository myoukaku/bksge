/**
 *	@file	empty.hpp
 *
 *	@brief	empty 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_EMPTY_HPP
#define BKSGE_FND_ITERATOR_EMPTY_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411)

namespace bksge
{

using std::empty;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
BKSGE_NODISCARD BKSGE_CONSTEXPR auto empty(Container const& c) -> decltype(c.empty())
{
	return c.empty();
}

template <typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CONSTEXPR bool empty(T const (&)[N]) BKSGE_NOEXCEPT
{
	return false;
}

template <typename E>
BKSGE_NODISCARD BKSGE_CONSTEXPR bool empty(std::initializer_list<E> il) BKSGE_NOEXCEPT
{
	return il.size() == 0;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_EMPTY_HPP
