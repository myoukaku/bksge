/**
 *	@file	arithmetic_promote.hpp
 *
 *	@brief	arithmetic_promote の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP
#define BKSGE_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP

namespace bksge
{

/**
 *	@brief
 */
template <typename... T>
struct arithmetic_promote;

/**
 *	@brief	arithmetic_promoteのエイリアステンプレート
 */
template <typename... T>
using arithmetic_promote_t = typename arithmetic_promote<T...>::type;

}	// namespace bksge

#include <bksge/type_traits/inl/arithmetic_promote_inl.hpp>

#endif // BKSGE_TYPE_TRAITS_ARITHMETIC_PROMOTE_HPP
