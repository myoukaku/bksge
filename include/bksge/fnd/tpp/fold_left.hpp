/**
 *	@file	fold_left.hpp
 *
 *	@brief	fold_left の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TPP_FOLD_LEFT_HPP
#define BKSGE_FND_TPP_FOLD_LEFT_HPP

#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace tpp
{

/**
 *	@brief	左畳み込み(引数が1つのときの特殊化)
 */
template <typename BinaryOperation, typename T>
inline BKSGE_CONSTEXPR bksge::remove_cvref_t<T>
fold_left(BinaryOperation, T&& t)
{
	return t;
}

/**
 *	@brief	左畳み込み
 */
template <typename BinaryOperation, typename A0, typename A1, typename... Args>
inline BKSGE_CONSTEXPR bksge::remove_cvref_t<A0>
fold_left(BinaryOperation binary_op, A0&& a0, A1&& a1, Args&&... args)
{
	return fold_left(binary_op,
		binary_op(bksge::forward<A0>(a0), bksge::forward<A1>(a1)),
		bksge::forward<Args>(args)...);
}

}	// namespace tpp

}	// namespace bksge

#endif // BKSGE_FND_TPP_FOLD_LEFT_HPP
