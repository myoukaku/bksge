/**
 *	@file	accumulate.hpp
 *
 *	@brief	accumulate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_ACCUMULATE_HPP
#define BKSGE_FND_NUMERIC_ACCUMULATE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	1つのシーケンスの任意の範囲の値を足し合わせる
 *
 *	@tparam	InputIterator	シーケンスのイテレータ型
 *	@tparam	T				集計結果の型
 *
 *	@param	first		シーケンスの先頭
 *	@param	last		シーケンスの終端
 *	@param	init		初期値
 *
 *	@return	集計結果の値
 */
template <typename InputIterator, typename T>
BKSGE_CXX14_CONSTEXPR T
accumulate(
	InputIterator first,
	InputIterator last,
	T init);

/**
 *	@brief	1つのシーケンスの任意の範囲の値を足し合わせる
 *
 *	@tparam	InputIterator	シーケンスのイテレータ型
 *	@tparam	T				集計結果の型
 *	@tparam	BinaryOperation	アキュムレータの型
 *
 *	@param	first		シーケンスの先頭
 *	@param	last		シーケンスの終端
 *	@param	init		初期値
 *	@param	binary_op	アキュームレータ。InputIteratorの要素型を2引数とり、その要素型を返す関数
 *
 *	@return	集計結果の値
 *
 *	@note	binary_opでシーケンスの要素を書き換えることと、
 *			イテレータを無効にすることは禁止されている。
 *			それ以外の操作は全て認められる。
 */
template <
	typename InputIterator,
	typename T,
	typename BinaryOperation
>
BKSGE_CXX14_CONSTEXPR T
accumulate(
	InputIterator first,
	InputIterator last,
	T init,
	BinaryOperation binary_op);

}	// namespace bksge

#include <bksge/fnd/numeric/inl/accumulate_inl.hpp>

#endif // BKSGE_FND_NUMERIC_ACCUMULATE_HPP
