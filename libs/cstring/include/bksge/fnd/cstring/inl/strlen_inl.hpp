/**
 *	@file	strlen_inl.hpp
 *
 *	@brief	strlen 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CSTRING_INL_STRLEN_INL_HPP
#define BKSGE_FND_CSTRING_INL_STRLEN_INL_HPP

#include <bksge/fnd/cstring/strlen.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

template <typename InputIterator>
inline BKSGE_CXX14_CONSTEXPR std::size_t
strlen(InputIterator first)
{
	std::size_t n = 0;
	
	while (*first++)
	{
		++n;
	}

	return n;
}

}	// namespace detail

inline BKSGE_CXX14_CONSTEXPR std::size_t
strlen(char const* str)
{
	return bksge::detail::strlen(str);
}

inline BKSGE_CXX14_CONSTEXPR std::size_t
strlen(wchar_t const* str)
{
	return bksge::detail::strlen(str);
}

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
inline BKSGE_CXX14_CONSTEXPR std::size_t
strlen(char8_t const* str)
{
	return bksge::detail::strlen(str);
}
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
inline BKSGE_CXX14_CONSTEXPR std::size_t
strlen(char16_t const* str)
{
	return bksge::detail::strlen(str);
}
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
inline BKSGE_CXX14_CONSTEXPR std::size_t
strlen(char32_t const* str)
{
	return bksge::detail::strlen(str);
}
#endif

}	// namespace bksge

#endif // BKSGE_FND_CSTRING_INL_STRLEN_INL_HPP
