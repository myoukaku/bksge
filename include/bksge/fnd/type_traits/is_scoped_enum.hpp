/**
 *	@file	is_scoped_enum.hpp
 *
 *	@brief	is_scoped_enum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_SCOPED_ENUM_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_scoped_enum) && (__cpp_lib_is_scoped_enum >= 202011)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename T>
struct is_scoped_enum
	: public detail::constant_wrapper<
		std::is_scoped_enum<T>
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/type_traits/negation.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bool = bksge::is_enum<T>::value>
struct is_scoped_enum_impl : public bksge::false_type {};

template <typename T>
struct is_scoped_enum_impl<T, true>
	: public bksge::negation<
		bksge::is_convertible<T, bksge::underlying_type_t<T>>
	>
{};

}	// namespace detail

/**
 *	@brief	型Tがスコープ付きの列挙型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_scoped_enumは、型Tがスコープ付きの列挙型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_scoped_enum
	: public detail::is_scoped_enum_impl<T>
{};

}	// namespace bksge

#endif

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

namespace bksge
{

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_scoped_enum_v = is_scoped_enum<T>::value;

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
