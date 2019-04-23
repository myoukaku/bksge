/**
 *	@file	blend_factor_inl.hpp
 *
 *	@brief	BlendFactor の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_BLEND_FACTOR_INL_HPP
#define BKSGE_RENDER_INL_BLEND_FACTOR_INL_HPP

#include <bksge/render/blend_factor.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(BlendFactor const& blend_factor)
{
#define BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(x)	{ x, #x }

	static std::unordered_map<BlendFactor, std::string> const m =
	{
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kZero),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kOne),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrcColor),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrcColor),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrcAlpha),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrcAlpha),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kDestAlpha),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvDestAlpha),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kDestColor),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvDestColor),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrcAlphaSaturate),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kBlendFactor),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvBlendFactor),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrc1Color),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrc1Color),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrc1Alpha),
		BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrc1Alpha),
	};

	return m.at(blend_factor);

#undef BKSGE_RENDER_MAKE_BLEND_FACTOR_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_BLEND_FACTOR_INL_HPP
