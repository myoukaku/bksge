/**
 *	@file	lexicographical_compare.hpp
 *
 *	@brief	lexicographical_compare の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define BKSGE_FND_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief	2つの範囲を辞書式順序で比較する
 *
 *	@tparam	InputIterator1
 *	@tparam	InputIterator2
 *	@tparam	Compare
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *	@param	comp
 *
 *	@return		範囲[first1, last1)が辞書式比較で範囲[first2, last2)より小さい場合trueを返す。
 *				そうでなければfalseを返す
 *
 *	@complexity	高々2*min((last1 - first1), (last2 - first2))回の比較が行われる。
 *
 *	@note		空のシーケンスは、空じゃないシーケンスより小さいと判断されるが、
 *				空のシーケンスに対しては小さくないと判断される。
 *				どちらかのシーケンスの横断が先に終わる場合(つまり、範囲の長さが合わない場合)、
 *				先に終わった方が小さいと判断される。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
lexicographical_compare(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	Compare comp);

/**
 *	@brief	2つの範囲を辞書式順序で比較する
 *
 *	@tparam	InputIterator1
 *	@tparam	InputIterator2
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *
 *	@return		範囲[first1, last1)が辞書式比較で範囲[first2, last2)より小さい場合trueを返す。
 *				そうでなければfalseを返す
 *
 *	@complexity	高々2*min((last1 - first1), (last2 - first2))回の比較が行われる。
 *
 *	@note		空のシーケンスは、空じゃないシーケンスより小さいと判断されるが、
 *				空のシーケンスに対しては小さくないと判断される。
 *				どちらかのシーケンスの横断が先に終わる場合(つまり、範囲の長さが合わない場合)、
 *				先に終わった方が小さいと判断される。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
lexicographical_compare(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2);

}	// namespace algorithm

using algorithm::lexicographical_compare;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/lexicographical_compare_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
