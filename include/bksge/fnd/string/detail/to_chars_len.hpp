/**
 *	@file	to_chars_len.hpp
 *
 *	@brief	to_chars_len の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_TO_CHARS_LEN_HPP
#define BKSGE_FND_STRING_DETAIL_TO_CHARS_LEN_HPP

#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR unsigned
to_chars_len(T value, int base = 10) noexcept
{
	static_assert(bksge::is_integral<T>::value, "");
	static_assert(bksge::is_unsigned<T>::value, "");

	unsigned int n = 1;
	const unsigned int  b2 = base * base;
	const unsigned int  b3 = b2   * base;
	const unsigned long b4 = b3   * base;
	for (;;)
	{
		if (value < (unsigned)base) { return n; }
		if (value < b2) { return n + 1; }
		if (value < b3) { return n + 2; }
		if (value < b4) { return n + 3; }
		value /= b4;
		n += 4;
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_TO_CHARS_LEN_HPP
