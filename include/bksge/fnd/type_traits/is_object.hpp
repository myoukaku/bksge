/**
 *	@file	is_object.hpp
 *
 *	@brief	is_object の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_OBJECT_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_OBJECT_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがオブジェクト型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_objectは、型Tがオブジェクト型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	オブジェクト型は、スカラ型、配列型、共用型、クラス型、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_object
	: public detail::constant_wrapper<
		std::is_object<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_OBJECT_HPP
