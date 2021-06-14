/**
 *	@file	is_assignable.hpp
 *
 *	@brief	is_assignable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_ASSIGNABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_ASSIGNABLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが型Uから代入可能か調べる。
 *
 *	@tparam		T
 *	@tparam		U
 *
 *	@require	型Tおよび型Uは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_assignableは、型Tが型Uから代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	declval<T>() = declval<U>()という実際には評価されない式が適格ならば代入可能であると判断される。
 */
template <typename T, typename U>
struct is_assignable
	: public detail::constant_wrapper<
		std::is_assignable<T, U>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_assignable_v = is_assignable<T, U>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_ASSIGNABLE_HPP
