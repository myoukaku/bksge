/**
 *	@file	is_char.hpp
 *
 *	@brief	is_char の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_IS_CHAR_HPP
#define BKSGE_FND_STRING_DETAIL_IS_CHAR_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
struct is_char : public bksge::false_type {};

template <>
struct is_char<char> : public bksge::true_type {};

template <>
struct is_char<wchar_t> : public bksge::true_type {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_IS_CHAR_HPP
