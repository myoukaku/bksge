/**
 *	@file	to_chars_10_impl.hpp
 *
 *	@brief	to_chars_10_impl の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_TO_CHARS_10_IMPL_HPP
#define BKSGE_FND_STRING_DETAIL_TO_CHARS_10_IMPL_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline void
to_chars_10_impl(char* first, bksge::size_t len, T val) noexcept
{
	static_assert(bksge::is_integral<T>::value, "");
	static_assert(bksge::is_unsigned<T>::value, "");

	static constexpr char digits[201] =
		"0001020304050607080910111213141516171819"
		"2021222324252627282930313233343536373839"
		"4041424344454647484950515253545556575859"
		"6061626364656667686970717273747576777879"
		"8081828384858687888990919293949596979899";
	bksge::size_t pos = len - 1;
	while (val >= 100)
	{
		auto const num = (val % 100) * 2;
		val /= 100;
		first[pos] = digits[num + 1];
		first[pos - 1] = digits[num];
		pos -= 2;
	}

	if (val >= 10)
	{
		auto const num = val * 2;
		first[1] = digits[num + 1];
		first[0] = digits[num];
	}
	else
	{
		first[0] = static_cast<char>('0' + val);
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_TO_CHARS_10_IMPL_HPP
