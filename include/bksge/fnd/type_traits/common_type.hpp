/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_COMMON_TYPE_HPP
#define BKSGE_FND_TYPE_TRAITS_COMMON_TYPE_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief	変換可能な共通の型を取得する。
 *
 *	@tparam		Types...
 *
 *	@require	Types...の全ての型は完全型であるか、void(cv修飾を含む)でなければならない。
 *
 *	common_typeは、Types...に含まれる全ての型が暗黙変換可能な型を、メンバ型typeとして定義する。
 */
using std::common_type;

template <typename... Types>
using common_type_t = typename common_type<Types...>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_COMMON_TYPE_HPP
