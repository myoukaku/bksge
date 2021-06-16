/**
 *	@file	float_promote.hpp
 *
 *	@brief	float_promote の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_FLOAT_PROMOTE_HPP
#define BKSGE_FND_TYPE_TRAITS_FLOAT_PROMOTE_HPP

namespace bksge
{

/**
 *	@brief	浮動小数点数への昇格
 *
 *	Types のどれか1つでも long double だったとき、type は long double
 *	Types が全て float だったとき、type は float
 *	それ以外のとき、type は double
 */
template <typename... Types>
struct float_promote;

/**
 *	@brief	float_promoteのエイリアステンプレート
 */
template <typename... Types>
using float_promote_t = typename float_promote<Types...>::type;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/float_promote_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_FLOAT_PROMOTE_HPP
