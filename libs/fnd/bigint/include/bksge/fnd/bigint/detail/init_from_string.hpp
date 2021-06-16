/**
 *	@file	init_from_string.hpp
 *
 *	@brief	init_from_string 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_INIT_FROM_STRING_HPP
#define BKSGE_FND_BIGINT_DETAIL_INIT_FROM_STRING_HPP

#include <bksge/fnd/bigint/detail/multiply.hpp>
#include <bksge/fnd/bigint/detail/add.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

namespace init_from_string_detail
{

template <typename CharT>
inline BKSGE_CXX14_CONSTEXPR int
sign_from_string(bksge::basic_string_view<CharT>* str)
{
	if (str->size() >= 1)
	{
		if ((*str)[0] == '-')
		{
			*str = str->substr(1);
			return -1;
		}
		else if ((*str)[0] == '+')
		{
			*str = str->substr(1);
		}
	}
	return 1;
}

template <typename ResultType, typename CharT>
inline BKSGE_CXX14_CONSTEXPR ResultType
base_from_string(bksge::basic_string_view<CharT>* str)
{
	if (str->size() >= 2)
	{
		if ((*str)[0] == '0')
		{
			switch ((*str)[1])
			{
			case 'b':	// 0b
			case 'B':	// 0B
				*str = str->substr(2);
				return 2;
			case 'x':	// 0x
			case 'X':	// 0X
				*str = str->substr(2);
				return 16;
			default:	// 0
				*str = str->substr(1);
				return 8;
			}
		}
	}
	return 10;
}

template <typename ResultType>
inline BKSGE_CXX14_CONSTEXPR ResultType
char_to_int(char c)
{
	if ('0' <= c && c <= '9')
	{
		return c - '0';
	}
	else if ('a' <= c && c <= 'f')
	{
		return c - 'a' + 10;
	}
	else if ('A' <= c && c <= 'F')
	{
		return c - 'A' + 10;
	}
	else
	{
		bksge::throw_runtime_error("");
	}
}

template <typename ElementType, typename CharT>
inline BKSGE_CXX14_CONSTEXPR ElementType
init_from_string_sub(bksge::basic_string_view<CharT>* str, bksge::size_t count, ElementType base, ElementType* out_multiplier)
{
	ElementType base_multiplier = 1;
	ElementType val = 0;
	bksge::size_t i = 0;
	for (auto c : *str)
	{
		auto const n = char_to_int<ElementType>(c);
		if (n >= base)
		{
			bksge::throw_runtime_error("");
		}

		val = val * base + n;
		base_multiplier *= base;
		++i;
		if (i >= count)
		{
			break;
		}
	}
	*out_multiplier = base_multiplier;
	*str = str->substr(i);
	return val;
}

}	// namespace init_from_string_detail

template <typename VectorType, typename CharT>
inline BKSGE_CXX14_CONSTEXPR int
init_from_string(VectorType& value, bksge::basic_string_view<CharT> str)
{
	using element_type = bksge::ranges::range_value_t<VectorType>;

	auto const sign = init_from_string_detail::sign_from_string(&str);
	auto const base = init_from_string_detail::base_from_string<element_type>(&str);

	bksge::size_t const count =
		base == 16 ?    bksge::numeric_limits<element_type>::digits / 4 - 1 :
		base == 10 ?    bksge::numeric_limits<element_type>::digits10 :
		base == 8 ?     bksge::numeric_limits<element_type>::digits / 3 - 1 :
		/*base == 2 ?*/ bksge::numeric_limits<element_type>::digits;

	value = {0};
	while (!str.empty())
	{
		element_type base_multiplier = 1;
		element_type val = init_from_string_detail::init_from_string_sub(
			&str, count, base, &base_multiplier);

		value = bigint_algo::multiply(value, base_multiplier);
		bigint_algo::add(value, val);
	}

	return sign;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_INIT_FROM_STRING_HPP
