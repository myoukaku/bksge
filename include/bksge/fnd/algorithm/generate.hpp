/**
 *	@file	generate.hpp
 *
 *	@brief	generate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_GENERATE_HPP
#define BKSGE_FND_ALGORITHM_GENERATE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		出力の範囲へ関数の結果を書き込む
 *
 *	@tparam		ForwardIterator
 *	@tparam		Generator
 *
 *	@param		first
 *	@param		last
 *	@param		gen
 *
 *	@require	gen は引数を取らないこと。
 *
 *	@effect		[first,last) のそれぞれのイテレータについて
 *				関数オブジェクト gen を呼び出し、その戻り値を代入する。
 *
 *	@complexity	正確に last - first 回の gen の呼び出しと代入が行われる。
 */
template <typename ForwardIterator, typename Generator>
BKSGE_CXX14_CONSTEXPR void
generate(ForwardIterator first, ForwardIterator last, Generator gen);

}	// namespace algorithm

using algorithm::generate;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/generate_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_GENERATE_HPP
