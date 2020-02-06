/**
 *	@file	blend_factor.hpp
 *
 *	@brief	BlendFactor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_BLEND_FACTOR_HPP
#define BKSGE_CORE_RENDER_BLEND_FACTOR_HPP

#include <bksge/core/render/fwd/blend_factor_fwd.hpp>
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

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <functional>
#include <cstddef>

namespace std
{

template<>
struct hash<bksge::render::BlendFactor>
{
	std::size_t operator()(bksge::render::BlendFactor const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::BlendFactor>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/blend_factor_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_BLEND_FACTOR_HPP
