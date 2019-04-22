/**
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

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_BLEND_FACTOR_HPP
