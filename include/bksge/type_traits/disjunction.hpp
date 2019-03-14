/**
 *	@file	disjunction.hpp
 *
 *	@brief	disjunction の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_DISJUNCTION_HPP
#define BKSGE_TYPE_TRAITS_DISJUNCTION_HPP

#include <type_traits>

#if defined(__cpp_lib_logical_traits) && (__cpp_lib_logical_traits >= 201510)

namespace bksge
{

using std::disjunction;

}	// namespace bksge

#else

namespace bksge
{

/**
 *	@brief		コンパイル時の論理OR
 *
 *	@tparam		B
 *
 *	disjunction<B1, ..., Bn> は最初にBi::value != false となるBiから派生する。
 *	もし全てのBiにおいて Bi::value == false ならBnから派生する。
 *	sizeof...(B) == 0 のときは、false_typeから派生する。
 *
 *	disjunctionはショート・サーキットされる：もしBi::value != falseとなったら、
 *	それ以降のBiはインスタンス化されない。
 *
 *	備考：
 *	Bは必ずしもtrue_typeまたはfalse_typeから派生している必要はない。
 *	B::valueを持っていて、B::valueがboolに変換可能であれば良い。
 *	例)
 *	disjunction<integral_constant<int, 2>, integral_constant<int, 4>>::value
 *	は 2 になる。
 */
template <typename... B>
struct disjunction;

}	// namespace bksge

#include <bksge/type_traits/inl/disjunction_inl.hpp>

#endif

#endif // BKSGE_TYPE_TRAITS_DISJUNCTION_HPP
