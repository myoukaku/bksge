﻿/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_BLEND_FACTOR_HPP
#define BKSGE_RENDER_BLEND_FACTOR_HPP

#include <bksge/render/fwd/blend_factor_fwd.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ブレンド時の係数
 */
enum class BlendFactor : std::uint32_t
{
	kZero,
	kOne,
	kSrcColor,
	kInvSrcColor,
	kSrcAlpha,
	kInvSrcAlpha,
	kDestAlpha,
	kInvDestAlpha,
	kDestColor,
	kInvDestColor,
	kSrcAlphaSaturate,
	kBlendFactor,
	kInvBlendFactor,
	kSrc1Color,
	kInvSrc1Color,
	kSrc1Alpha,
	kInvSrc1Alpha,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(BlendFactor const& blend_factor);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, BlendFactor const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_STD_VER <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::BlendFactor>
{
	std::size_t operator()(bksge::render::BlendFactor const& arg) const
	{
		using underlying_type =
			typename std::underlying_type<bksge::render::BlendFactor>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_STD_VER <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/blend_factor_inl.hpp>
#endif

#endif // BKSGE_RENDER_BLEND_FACTOR_HPP
