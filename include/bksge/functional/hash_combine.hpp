/**
 *	@file	hash_combine.hpp
 *
 *	@brief	hash_combine 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FUNCTIONAL_HASH_COMBINE_HPP
#define BKSGE_FUNCTIONAL_HASH_COMBINE_HPP

#include <bksge/config.hpp>
#include <cstddef>	// size_t

namespace bksge
{

/**
 *	@brief	hash_combine
 *
 *	複数の値からハッシュ値を計算する
 */
template <typename RT = std::size_t, typename... T>
RT hash_combine(T const&... args) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/functional/inl/hash_combine_inl.hpp>

#endif // BKSGE_FUNCTIONAL_HASH_COMBINE_HPP
