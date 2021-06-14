/**
 *	@file	is_fundamental.hpp
 *
 *	@brief	is_fundamental の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_FUNDAMENTAL_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが単純型(Fundamental types)か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_fundamentalは、型Tが単純型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	単純型は、算術型、void、nullptr_t、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_fundamental
	: public detail::constant_wrapper<
		std::is_fundamental<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_fundamental_v = is_fundamental<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
