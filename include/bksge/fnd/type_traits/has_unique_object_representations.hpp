/**
 *	@file	has_unique_object_representations.hpp
 *
 *	@brief	has_unique_object_representations の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
#define BKSGE_FND_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		同じ値を持つT型のオブジェクトが同じオブジェクト表現を持つか
 *
 *	@tparam		T	チェックする型
 *
 *	has_unique_object_representationsは、
 *	型TがTriviallyCopyableかつ、
 *	同じ値を持つT型のオブジェクトが同じオブジェクト表現を持つ場合、
 *	true_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	@note		T型が、不完全型であるか、
 *				void(cv修飾を含む)であるか、
 *				要素数不明の配列である場合、動作は未定義。
 */
template <typename T>
struct has_unique_object_representations;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool has_unique_object_representations_v = has_unique_object_representations<T>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/has_unique_object_representations_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_HAS_UNIQUE_OBJECT_REPRESENTATIONS_HPP
