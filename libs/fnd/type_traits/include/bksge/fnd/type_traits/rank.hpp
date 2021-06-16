/**
 *	@file	rank.hpp
 *
 *	@brief	rank の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_RANK_HPP
#define BKSGE_FND_TYPE_TRAITS_RANK_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	配列型の次元数を取得する。
 *
 *	@tparam		T
 *
 *	型Tが配列型である場合、配列の次元数となる整数値をメンバ定数valueの値として定義する。
 *	配列型でなければ0をメンバ定数valueの値として定義する。
 */
template <typename T>
struct rank
	: public detail::constant_wrapper<
		std::rank<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bksge::size_t rank_v = rank<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_RANK_HPP
