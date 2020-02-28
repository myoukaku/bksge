/**
 *	@file	size.hpp
 *
 *	@brief	size 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_SIZE_HPP
#define BKSGE_FND_ITERATOR_SIZE_HPP

#include <iterator>

#if defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411)

namespace bksge
{

using std::size;

}	// namespace bksge

#else

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename Container>
BKSGE_NODISCARD BKSGE_CONSTEXPR auto size(Container const& c) -> decltype(c.size())
{
	return c.size();
}

template <typename T, bksge::size_t N>
BKSGE_NODISCARD BKSGE_CONSTEXPR bksge::size_t size(T const (&)[N]) BKSGE_NOEXCEPT
{
	return N;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_SIZE_HPP
