/**
 *	@file	is_member_pointer.hpp
 *
 *	@brief	is_member_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_MEMBER_POINTER_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがメンバポインタ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_pointerは、型Tがメンバポインタ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	メンバポインタ型は、データメンバへのポインタ型、
 *	メンバ関数へのポインタ型、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_member_pointer
	: public detail::constant_wrapper<
		std::is_member_pointer<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
