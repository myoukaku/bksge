/**
 *	@file	addressof.hpp
 *
 *	@brief	addressof を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_ADDRESSOF_HPP
#define BKSGE_FND_MEMORY_ADDRESSOF_HPP

#include <memory>

#if defined(__cpp_lib_addressof_constexpr) && (__cpp_lib_addressof_constexpr >= 201603)

namespace bksge
{

using std::addressof;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	変数のアドレスを必ず取得する
 *
 *	operator&をオーバーロードしたクラスであっても、そのオブジェクトのアドレスを取得できる。
 *
 *	operator&がオーバーロードされていない場合、constexprにできる。
 *	operator&がオーバーロードされている場合、constexprにできない。
 *	(C++17以降はstd::addressofがconstexprになるのでconstexprにできる)
 */
template <typename T>
BKSGE_CONSTEXPR T* addressof(T& r) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/memory/inl/addressof_inl.hpp>

#endif

#endif // BKSGE_FND_MEMORY_ADDRESSOF_HPP
