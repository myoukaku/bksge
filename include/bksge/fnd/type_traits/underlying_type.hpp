/**
 *	@file	underlying_type.hpp
 *
 *	@brief	underlying_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_UNDERLYING_TYPE_HPP
#define BKSGE_FND_TYPE_TRAITS_UNDERLYING_TYPE_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		enumの基底型を取得する
 *
 *	@tparam		T
 *
 *	@require	型Tが列挙型であること。
 *
 *	underlying_typeは、列挙型Tの基底型を、メンバ型typeとして定義する。
 */
using std::underlying_type;

/**
 *	@brief	underlying_typeのエイリアステンプレート
 */
template <typename T>
using underlying_type_t = typename underlying_type<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_UNDERLYING_TYPE_HPP
