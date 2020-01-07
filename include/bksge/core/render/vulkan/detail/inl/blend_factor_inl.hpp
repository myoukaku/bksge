/**
 *	@file	blend_factor_inl.hpp
 *
 *	@brief	BlendFactor の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_FACTOR_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_FACTOR_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/blend_factor.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/blend_factor.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkBlendFactor
ToVulkanBlendFactor(bksge::BlendFactor blend_factor)
{
	switch (blend_factor)
	{
	case bksge::BlendFactor::kZero:             return VK_BLEND_FACTOR_ZERO;
	case bksge::BlendFactor::kOne:              return VK_BLEND_FACTOR_ONE;
	case bksge::BlendFactor::kSrcColor:         return VK_BLEND_FACTOR_SRC_COLOR;
	case bksge::BlendFactor::kInvSrcColor:      return VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;
	case bksge::BlendFactor::kSrcAlpha:         return VK_BLEND_FACTOR_SRC_ALPHA;
	case bksge::BlendFactor::kInvSrcAlpha:      return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	case bksge::BlendFactor::kDestAlpha:        return VK_BLEND_FACTOR_DST_ALPHA;
	case bksge::BlendFactor::kInvDestAlpha:     return VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA;
	case bksge::BlendFactor::kDestColor:        return VK_BLEND_FACTOR_DST_COLOR;
	case bksge::BlendFactor::kInvDestColor:     return VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR;
	case bksge::BlendFactor::kSrcAlphaSaturate: return VK_BLEND_FACTOR_SRC_ALPHA_SATURATE;
	case bksge::BlendFactor::kBlendFactor:      return VK_BLEND_FACTOR_CONSTANT_COLOR;
	case bksge::BlendFactor::kInvBlendFactor:   return VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR;
	case bksge::BlendFactor::kSrc1Color:        return VK_BLEND_FACTOR_SRC1_COLOR;
	case bksge::BlendFactor::kInvSrc1Color:     return VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR;
	case bksge::BlendFactor::kSrc1Alpha:        return VK_BLEND_FACTOR_SRC1_ALPHA;
	case bksge::BlendFactor::kInvSrc1Alpha:     return VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA;
	}
	return VK_BLEND_FACTOR_ZERO;
}

}	// namespace detail

BKSGE_INLINE
BlendFactor::BlendFactor(bksge::BlendFactor blend_factor)
	: m_blend_factor(detail::ToVulkanBlendFactor(blend_factor))
{}

BKSGE_INLINE
BlendFactor::operator VkBlendFactor() const
{
	return m_blend_factor;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_FACTOR_INL_HPP
