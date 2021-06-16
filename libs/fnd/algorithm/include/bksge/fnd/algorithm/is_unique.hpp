/**
 *	@file	is_unique.hpp
 *
 *	@brief	is_unique 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_IS_UNIQUE_HPP
#define BKSGE_FND_ALGORITHM_IS_UNIQUE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		与えられた範囲に重複した要素がないかどうか取得する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		与えられた範囲に重複した要素がなければtrue
 *
 *	@complexity
 */
template <typename ForwardIterator>
BKSGE_CONSTEXPR bool
is_unique(ForwardIterator first, ForwardIterator last);

/**
 *	@brief		与えられた範囲に重複した要素がないかどうか取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		与えられた範囲に重複した要素がなければtrue
 *
 *	@complexity
 */
template <typename ForwardIterator, typename Compare>
BKSGE_CONSTEXPR bool
is_unique(ForwardIterator first, ForwardIterator last, Compare comp);

}	// namespace algorithm

using algorithm::is_unique;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/is_unique_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_IS_UNIQUE_HPP
