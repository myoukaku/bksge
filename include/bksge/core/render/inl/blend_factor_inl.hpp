﻿/**
 *	@file	blend_factor_inl.hpp
 *
 *	@brief	BlendFactor の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_BLEND_FACTOR_INL_HPP
#define BKSGE_CORE_RENDER_INL_BLEND_FACTOR_INL_HPP

#include <bksge/core/render/blend_factor.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(BlendFactor const& blend_factor)
{
#define BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(x)	{ x, #x }

	static std::unordered_map<BlendFactor, std::string> const m =
	{
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kZero),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kOne),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrcColor),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrcColor),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrcAlpha),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrcAlpha),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kDestAlpha),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvDestAlpha),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kDestColor),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvDestColor),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrcAlphaSaturate),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kBlendFactor),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvBlendFactor),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrc1Color),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrc1Color),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kSrc1Alpha),
		BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP(BlendFactor::kInvSrc1Alpha),
	};

	return m.at(blend_factor);

#undef BKSGE_CORE_RENDER_MAKE_BLEND_FACTOR_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_BLEND_FACTOR_INL_HPP
