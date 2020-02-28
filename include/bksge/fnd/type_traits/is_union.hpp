/**
 *	@file	is_union.hpp
 *
 *	@brief	is_union の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_UNION_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_UNION_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが共用型かを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_unionは、型Tが共用型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_union
	: public detail::constant_wrapper<
		std::is_union<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_UNION_HPP
