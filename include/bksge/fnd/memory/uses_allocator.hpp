/**
 *	@file	uses_allocator.hpp
 *
 *	@brief	uses_allocator を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_USES_ALLOCATOR_HPP
#define BKSGE_FND_MEMORY_USES_ALLOCATOR_HPP

#include <memory>

namespace bksge
{

/**
 *	@brief	型Tがアロケータを使用するかを調べる。
 *
 *	このクラスがtrue_typeから派生する場合、以下のコンストラクタ初期化が可能である：
 *
 *	・T(allocator_arg_t, alloc, args...)のように、第1引数にallocator_arg_t、
 *	　第2引数にアロケータオブジェクトをとる構築。
 *	・T(args..., alloc)のように、最後の引数としてアロケータオブジェクトをとる構築。
 *
 *	このクラスは、scoped_allocator_adaptorクラスで使用される。
 */
using std::uses_allocator;

}	// namespace bksge

#endif // BKSGE_FND_MEMORY_USES_ALLOCATOR_HPP
