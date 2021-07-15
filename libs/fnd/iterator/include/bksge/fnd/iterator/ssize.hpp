/**
 *	@file	ssize.hpp
 *
 *	@brief	ssize 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_SSIZE_HPP
#define BKSGE_FND_ITERATOR_SSIZE_HPP

//#include <iterator>

#if 0//defined(__cpp_lib_nonmember_container_access) && (__cpp_lib_nonmember_container_access >= 201411)

namespace bksge
{

using std::ssize;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/make_signed.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <typename C>
BKSGE_CONSTEXPR auto ssize(C const& c)
-> bksge::common_type_t<
	std::ptrdiff_t,
	bksge::make_signed_t<decltype(c.size())>>
{
	using R = bksge::common_type_t<
		std::ptrdiff_t,
		bksge::make_signed_t<decltype(c.size())>>;
	return static_cast<R>(c.size());
}

template <typename T, std::ptrdiff_t N>
BKSGE_CONSTEXPR std::ptrdiff_t
ssize(T const(&)[N]) BKSGE_NOEXCEPT
{
	return N;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_ITERATOR_SSIZE_HPP
