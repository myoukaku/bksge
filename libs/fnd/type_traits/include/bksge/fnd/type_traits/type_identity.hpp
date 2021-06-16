/**
 *	@file	type_identity.hpp
 *
 *	@brief	type_identity の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define BKSGE_FND_TYPE_TRAITS_TYPE_IDENTITY_HPP

#include <type_traits>

#if defined(__cpp_lib_type_identity) && (__cpp_lib_type_identity >= 201806)

namespace bksge
{

using std::type_identity;
using std::type_identity_t;

}	// namespace bksge

#else

namespace bksge
{

/**
 *	@brief		type_identity
 *
 *	@tparam		T
 *
 *	type_identityは型Tをメンバ型typeとして定義する。
 */
template <typename T>
struct type_identity
{
	using type = T;
};

/**
 *	@brief	type_identityのエイリアステンプレート
 */
template <typename T>
using type_identity_t = typename type_identity<T>::type;

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_TYPE_IDENTITY_HPP
