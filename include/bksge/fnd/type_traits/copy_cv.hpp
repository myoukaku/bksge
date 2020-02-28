/**
 *	@file	copy_cv.hpp
 *
 *	@brief	copy_cv の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_COPY_CV_HPP
#define BKSGE_FND_TYPE_TRAITS_COPY_CV_HPP

namespace bksge
{

/**
 *	@brief	cv修飾をコピーする
 *
 *	@tparam	T	基本となる型
 *	@tparam	U	cv修飾のコピー元
 *
 *	Uのcv修飾をTにコピーした型をメンバ型typeとして定義する。
 *
 *	例)
 *	copy_cv<int, void>::type                -> int
 *	copy_cv<int const, void>::type          -> int const
 *	copy_cv<int, void const>::type          -> int const
 *	copy_cv<int volatile, void const>::type -> int const volatile
 *	copy_cv<int&, void const>::type         -> int&
 *	copy_cv<int*, void volatile>::type      -> int* volatile
 */
template <typename T, typename U>
struct copy_cv;

/**
 *	@brief	copy_cvのエイリアス
 */
template <typename T, typename U>
using copy_cv_t = typename copy_cv<T, U>::type;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/copy_cv_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_COPY_CV_HPP
