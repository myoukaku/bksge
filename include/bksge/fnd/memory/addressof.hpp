/**
 *	@file	addressof.hpp
 *
 *	@brief	addressof を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_ADDRESSOF_HPP
#define BKSGE_FND_MEMORY_ADDRESSOF_HPP

#include <bksge/fnd/config.hpp>

#if BKSGE_CXX_STANDARD >= 17

#include <memory>

namespace bksge
{

using std::addressof;

}	// namespace bksge

#else

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

/**
 *	@brief	右辺値を取るオーバーロードは削除
 */
template <typename T>
T const* addressof(T const&&) = delete;

}	// namespace bksge

#include <bksge/fnd/memory/inl/addressof_inl.hpp>

#endif

#endif // BKSGE_FND_MEMORY_ADDRESSOF_HPP
