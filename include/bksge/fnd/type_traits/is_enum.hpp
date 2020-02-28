/**
 *	@file	is_enum.hpp
 *
 *	@brief	is_enum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_ENUM_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_ENUM_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが列挙型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない
 *
 *	is_enumは、型Tが列挙型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_enum
	: public detail::constant_wrapper<
		std::is_enum<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_ENUM_HPP
