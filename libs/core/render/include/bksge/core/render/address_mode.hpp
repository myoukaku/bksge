/**
 *	@file	address_mode.hpp
 *
 *	@brief	AddressMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_ADDRESS_MODE_HPP
#define BKSGE_CORE_RENDER_ADDRESS_MODE_HPP

#include <bksge/core/render/fwd/address_mode_fwd.hpp>
#include <bksge/fnd/string/string.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	テクスチャ座標がテクスチャのサイズを超えた時の補正方法
 */
enum class AddressMode : bksge::uint32_t
{
	kRepeat, ///< 繰り返し
	kMirror, ///< 反転しながら繰り返す
	kClamp,	 ///< [0, 1]の範囲にクランプ
	kBorder, ///< テクスチャの境界色として指定された色にする
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(AddressMode const& address_mode);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, AddressMode const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/address_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_ADDRESS_MODE_HPP
