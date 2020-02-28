/**
 *	@file	is_floating_point.hpp
 *
 *	@brief	is_floating_point の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_FLOATING_POINT_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが浮動小数点型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_floating_pointは、型Tが浮動小数点型(cv修飾を許容する)であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_floating_point
	: public detail::constant_wrapper<
		std::is_floating_point<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_FLOATING_POINT_HPP
