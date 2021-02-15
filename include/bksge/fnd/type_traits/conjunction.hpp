/**
 *	@file	conjunction.hpp
 *
 *	@brief	conjunction の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_CONJUNCTION_HPP
#define BKSGE_FND_TYPE_TRAITS_CONJUNCTION_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_logical_traits) && (__cpp_lib_logical_traits >= 201510)

namespace bksge
{

using std::conjunction;

}	// namespace bksge

#else

namespace bksge
{

/**
 *	@brief		コンパイル時の論理AND
 *
 *	@tparam		B
 *
 *	conjunction<B1, ..., Bn> は最初にBi::value == false となるBiから派生する。
 *	もし全てのBiにおいて Bi::value != false ならBnから派生する。
 *	sizeof...(B) == 0 のときは、true_typeから派生する。
 *
 *	conjunctionはショート・サーキットされる：もしBi::value == falseとなったら、
 *	それ以降のBiはインスタンス化されない。
 *
 *	備考：
 *	Bは必ずしもtrue_typeまたはfalse_typeから派生している必要はない。
 *	B::valueを持っていて、B::valueがboolに変換可能であれば良い。
 *	例)
 *	conjunction<integral_constant<int, 2>, integral_constant<int, 4>>::value
 *	は 4 になる。
 */
template <typename... B>
struct conjunction;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/conjunction_inl.hpp>

#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename... B>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool conjunction_v = conjunction<B...>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_CONJUNCTION_HPP
