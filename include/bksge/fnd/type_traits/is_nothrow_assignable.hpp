/**
 *	@file	is_nothrow_assignable.hpp
 *
 *	@brief	is_nothrow_assignable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが型Uから代入可能で、かつ代入操作が例外を投げないかを調べる。
 *
 *	@tparam		T
 *	@tparam		U
 *
 *	@require	型Tおよび型Uは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_nothrow_assignableは、型Tが型Uから例外を投げない保証のもとに代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	is_assignable<T, U>::value == trueかつ、いかなる例外も投げないならば、
 *	例外を投げない代入が可能であると判断される。
 */
template <typename T, typename U>
struct is_nothrow_assignable
	: public detail::constant_wrapper<
		std::is_nothrow_assignable<T, U>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_ASSIGNABLE_HPP
