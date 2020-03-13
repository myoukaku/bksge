/**
 *	@file	data.hpp
 *
 *	@brief	data 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_DATA_HPP
#define BKSGE_FND_ITERATOR_DATA_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411)

namespace bksge
{

using std::data;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <initializer_list>

namespace bksge
{

template <typename Container>
BKSGE_NODISCARD BKSGE_CONSTEXPR auto data(Container& c) -> decltype(c.data())
{
	return c.data();
}

template <typename Container>
BKSGE_NODISCARD BKSGE_CONSTEXPR auto data(Container const& c) -> decltype(c.data())
{
	return c.data();
}

template <typename T, std::size_t N>
BKSGE_NODISCARD BKSGE_CONSTEXPR T* data(T (&a)[N]) BKSGE_NOEXCEPT
{
	return a;
}

template <typename E>
BKSGE_NODISCARD BKSGE_CONSTEXPR E const* data(std::initializer_list<E> il) BKSGE_NOEXCEPT
{
	return il.begin();
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_DATA_HPP
