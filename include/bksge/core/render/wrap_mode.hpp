/**
 *	@file	wrap_mode.hpp
 *
 *	@brief	WrapMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_WRAP_MODE_HPP
#define BKSGE_CORE_RENDER_WRAP_MODE_HPP

#include <bksge/core/render/fwd/wrap_mode_fwd.hpp>
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

#if BKSGE_CXX_STANDARD <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::WrapMode>
{
	std::size_t operator()(bksge::render::WrapMode const& arg) const
	{
		using underlying_type = typename std::underlying_type<bksge::render::WrapMode>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/wrap_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_WRAP_MODE_HPP
