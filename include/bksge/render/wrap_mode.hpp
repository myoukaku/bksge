﻿/**
 *	@file	wrap_mode.hpp
 *
 *	@brief	WrapMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_WRAP_MODE_HPP
#define BKSGE_RENDER_WRAP_MODE_HPP

#include <bksge/render/fwd/wrap_mode_fwd.hpp>
#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	テクスチャ座標がテクスチャのサイズを超えた時の補正方法
 */
enum class WrapMode
{
	kRepeat, ///< 繰り返し
	kClamp,	 ///< [0, 1]の範囲にクランプ
	kBorder, ///< テクスチャの境界色として指定された色にする
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(WrapMode const& wrap_mode);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, WrapMode const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/wrap_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_WRAP_MODE_HPP
