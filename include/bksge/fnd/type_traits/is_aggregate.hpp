/**
 *	@file	is_aggregate.hpp
 *
 *	@brief	is_aggregate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_AGGREGATE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_AGGREGATE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが集成体か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	remove_all_extents_t<T>した結果の型が、完全型であるか、
 *				void(cv修飾を含む)でなければならない。
 *
 *	is_aggregateは、型Tが集成体 (cv修飾を許容する) であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	型Tが集成体であるための条件は以下である：
 *	・ユーザー定義されたコンストラクタ、explicitなコンストラクタ、継承コンストラクタを持たない
 *	・private／protectedな非静的メンバ変数を持たない
 *	・仮想関数を持たない
 *	・仮想基本クラス、private／protected基本クラスを持たない
 */
#if defined(__cpp_lib_is_aggregate) && (__cpp_lib_is_aggregate >= 201703)

template <typename T>
struct is_aggregate
	: public detail::constant_wrapper<
		std::is_aggregate<T>
	>
{};

#define BKSGE_HAS_CXX17_IS_AGGREGATE

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_AGGREGATE_HPP
