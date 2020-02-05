﻿/**
 *	@file	clear_flag.hpp
 *
 *	@brief	ClearFlag の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_CLEAR_FLAG_HPP
#define BKSGE_CORE_RENDER_CLEAR_FLAG_HPP

#include <bksge/core/render/fwd/clear_flag_fwd.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	バッファのクリアに指定するフラグ
 */
enum class ClearFlag : std::uint32_t
{
	/// クリアしない
	kNone    = 0,

	/// 色バッファをクリアする
	kColor   = (1 << 0),

	/// デプスバッファをクリアする
	kDepth   = (1 << 1),

	/// ステンシルバッファをクリアする
	kStencil = (1 << 2),

	/// 全てのバッファをクリアする
	kAll = kColor | kDepth | kStencil,
};

BKSGE_CONSTEXPR ClearFlag
operator|(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CONSTEXPR ClearFlag
operator&(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CONSTEXPR ClearFlag
operator^(ClearFlag lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ClearFlag&
operator|=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ClearFlag&
operator&=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ClearFlag&
operator^=(ClearFlag& lhs, ClearFlag rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	文字列への変換
 */
std::string to_string(ClearFlag const& clear_flag);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, ClearFlag rhs)
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
struct hash<bksge::render::ClearFlag>
{
	std::size_t operator()(bksge::render::ClearFlag const& arg) const
	{
		using underlying_type = typename std::underlying_type<bksge::render::ClearFlag>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/core/render/inl/clear_flag_inl.hpp>

#endif // BKSGE_CORE_RENDER_CLEAR_FLAG_HPP
