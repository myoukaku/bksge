/**
 *	@file	to_basic_string.hpp
 *
 *	@brief	to_basic_string 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_TO_BASIC_STRING_HPP
#define BKSGE_FND_BIGINT_DETAIL_TO_BASIC_STRING_HPP

#include <bksge/fnd/bigint/detail/convert_radix.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename CharT, typename VectorType>
inline bksge::basic_string<CharT>
to_basic_string(VectorType const& value)
{
	// 10進に変換して
	auto baseN_value = bigint_algo::convert_radix<10>(value);

	// 文字列化する
	bksge::basic_string<CharT> r;
	for (auto it = baseN_value.rbegin(); it != baseN_value.rend(); ++it)
	{
		r += static_cast<CharT>((*it) + '0');
	}

	return r;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_TO_BASIC_STRING_HPP
