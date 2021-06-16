/**
 *	@file	make_unsigned.hpp
 *
 *	@brief	make_unsigned の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define BKSGE_FND_TYPE_TRAITS_MAKE_UNSIGNED_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief	整数型を符号なしにする。
 *
 *	@tparam		T
 *
 *	@require	型Tが、整数型もしくは列挙型(cv修飾を許容する)であること。ただしboolは許可されない。
 *
 *	make_unsignedは、型Tに対応する符号なし整数型を、メンバ型typeとして定義する。
 *	型Tがcv修飾されていた場合は、メンバ型typeにも同じcv修飾が付加される。
 */
using std::make_unsigned;

template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_MAKE_UNSIGNED_HPP
