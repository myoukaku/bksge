/**
 *	@file	const_pointer_cast.hpp
 *
 *	@brief	const_pointer_cast を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_CONST_POINTER_CAST_HPP
#define BKSGE_FND_MEMORY_CONST_POINTER_CAST_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	shared_ptr で管理するインスタンスに対して const_cast を行う。
 *
 *	@param	r
 *
 *	@return	r が空であった場合、この関数は空の shared_ptr<T> を返却する。
 *			空ではない場合、この関数は const_cast<T*> を行い shared_ptr<T> を返却する。
 *			この際、shared_ptr<U> の参照カウンタをそのまま使用する。
 *
 *	@note	shared_ptr<T>(const_cast<T*>(r.get())) という方法は動作未定義となるので使用しないこと。
 */
template <typename T, typename U>
inline shared_ptr<T>
const_pointer_cast(shared_ptr<U> const& r) BKSGE_NOEXCEPT
{
	using type = typename shared_ptr<T>::element_type;
	return shared_ptr<T>(r, const_cast<type*>(r.get()));
}

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_CONST_POINTER_CAST_HPP
