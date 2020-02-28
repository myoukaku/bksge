/**
 *	@file	is_compound.hpp
 *
 *	@brief	is_compound の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_COMPOUND_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_COMPOUND_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが複合型 (Compound types) か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_compoundは、型Tが複合型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	複合型は、配列型、関数型、ポインタ型、参照型、クラス型、
 *	共用型、列挙型、メンバポインタ型、およびそれらのcv修飾を含む。
 *
 *	複合型は、すべての型の集合から、単純型の集合を除いたものに等しい。
 */
template <typename T>
struct is_compound
	: public detail::constant_wrapper<
		std::is_compound<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_COMPOUND_HPP
