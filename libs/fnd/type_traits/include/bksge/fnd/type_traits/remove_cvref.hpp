/**
 *	@file	remove_cvref.hpp
 *
 *	@brief	remove_cvref の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_REMOVE_CVREF_HPP
#define BKSGE_FND_TYPE_TRAITS_REMOVE_CVREF_HPP

#include <type_traits>

#if defined(__cpp_lib_remove_cvref) && (__cpp_lib_remove_cvref >= 201711)

namespace bksge
{

using std::remove_cvref;
using std::remove_cvref_t;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>

namespace bksge
{

/**
 *	@brief		型TからCV修飾と参照を除去する。
 *
 *	@tparam		T
 */
template <typename T>
struct remove_cvref
	: public bksge::remove_cv<bksge::remove_reference_t<T>>
{};

/**
 *	@brief	remove_cvrefのエイリアステンプレート
 */
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_REMOVE_CVREF_HPP
