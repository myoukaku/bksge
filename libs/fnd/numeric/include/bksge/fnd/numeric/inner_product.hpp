/**
 *	@file	inner_product.hpp
 *
 *	@brief	inner_product の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_INNER_PRODUCT_HPP
#define BKSGE_FND_NUMERIC_INNER_PRODUCT_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	2つのシーケンスの任意の範囲の値の内積を計算する
 *
 *	@tparam	InputIterator1	1つめのシーケンスのイテレータの型
 *	@tparam	InputIterator2	2つめのシーケンスのイテレータの型
 *	@tparam	T				内積の値の型
 *
 *	@param	first1	1つめのシーケンスの先頭
 *	@param	last1	1つめのシーケンスの終端
 *	@param	first2	2つめのシーケンスの先頭
 *	@param	init	初期値
 *
 *	@return	シーケンスの内積の値
 *
 *	計算量：
 *		n を last1 - first1 としたとき、n 回の加算処理と n 回の乗算処理を行う
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename T
>
BKSGE_CXX14_CONSTEXPR T
inner_product(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	T init);

/**
 *	@brief	2つのシーケンスの任意の範囲の値の内積を計算する
 *
 *	@tparam	InputIterator1		1つめのシーケンスのイテレータの型
 *	@tparam	InputIterator2		2つめのシーケンスのイテレータの型
 *	@tparam	T					内積の値の型
 *	@tparam	BinaryOperation1	binary_op1の型
 *	@tparam	BinaryOperation2	binary_op2の型
 *
 *	@param	first1		1つめのシーケンスの先頭
 *	@param	last1		1つめのシーケンスの終端
 *	@param	first2		2つめのシーケンスの先頭
 *	@param	init		初期値
 *	@param	binary_op1	アキュームレータ
 *	@param	binary_op2	2つのシーケンスの対になる要素への処理
 *
 *	@return	シーケンスの内積の値
 *
 *	計算量：
 *		n を last1 - first1 としたとき、n 回の binary_op1 呼び出しと n 回の binary_op2 呼び出しを行う
 *
 *	@note	binary_op1,binary_op2でシーケンスの要素を書き換えることと、
 *			イテレータを無効にすることは禁止されている。
 *			それ以外の操作は全て認められる。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename T,
	typename BinaryOperation1,
	typename BinaryOperation2
>
BKSGE_CXX14_CONSTEXPR T
inner_product(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	T init,
	BinaryOperation1 binary_op1,
	BinaryOperation2 binary_op2);

}	// namespace bksge

#include <bksge/fnd/numeric/inl/inner_product_inl.hpp>

#endif // BKSGE_FND_NUMERIC_INNER_PRODUCT_HPP
