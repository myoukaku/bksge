/**
 *	@file	is_trivially_assignable.hpp
 *
 *	@brief	is_trivially_assignable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが型Uからトリビアルに代入可能か調べる。
 *
 *	@tparam		T
 *	@tparam		U
 *
 *	@require	型Tおよび型Uは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_trivially_assignableは、型Tが型Uからトリビアルに代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	「トリビアルに代入可能」とは、ユーザー定義されない代入演算子を持っているということを意味する。
 */
template <typename T, typename U>
struct is_trivially_assignable
	: public detail::constant_wrapper<
		std::is_trivially_assignable<T, U>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_trivially_assignable_v = is_trivially_assignable<T, U>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
