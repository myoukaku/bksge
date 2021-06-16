/**
 *	@file	to_address.hpp
 *
 *	@brief	to_address を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_TO_ADDRESS_HPP
#define BKSGE_FND_MEMORY_TO_ADDRESS_HPP

#include <memory>

#if defined(__cpp_lib_to_address) && (__cpp_lib_to_address >= 201711)

namespace bksge
{

using std::to_address;

}	// namespace bksge

#else

#include <bksge/fnd/memory/detail/to_address_impl.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		ポインタと見なせるオブジェクトからアドレスを取得する。
 *
 *	@param		p	仮想的なポインタ
 *
 *	@return		式pointer_traits<Ptr>::to_address(p)が有効であればその戻り値を返す。
 *				そうでなければ、to_address(p.operator->())を返す
 */
template <typename Ptr>
BKSGE_CONSTEXPR auto
to_address(const Ptr& p) BKSGE_NOEXCEPT
->decltype(detail::to_address_impl(p))
{
	return detail::to_address_impl(p);
}

/**
 *	@brief		ポインタと見なせるオブジェクトからアドレスを取得する。
 *
 *	@param		p	生ポインタ
 *
 *	@require	型Tが関数ではないこと
 *
 *	@return		pを返す
 */
template <typename T>
BKSGE_CONSTEXPR T*
to_address(T* p) BKSGE_NOEXCEPT
{
	return detail::to_address_impl(p);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_MEMORY_TO_ADDRESS_HPP
