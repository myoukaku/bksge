/**
 *	@file	blend_operation_inl.hpp
 *
 *	@brief	BlendOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/blend_operation.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/blend_operation.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkBlendOp
ToVulkanBlendOperation(bksge::BlendOperation blend_operation)
{
	switch (blend_operation)
	{
	case bksge::BlendOperation::kAdd:             return VK_BLEND_OP_ADD;
	case bksge::BlendOperation::kSubtract:        return VK_BLEND_OP_SUBTRACT;
	case bksge::BlendOperation::kReverseSubtract: return VK_BLEND_OP_REVERSE_SUBTRACT;
	case bksge::BlendOperation::kMin:             return VK_BLEND_OP_MIN;
	case bksge::BlendOperation::kMax:             return VK_BLEND_OP_MAX;
	}
	return VK_BLEND_OP_ADD;
}

}	// namespace detail

BKSGE_INLINE
BlendOperation::BlendOperation(bksge::BlendOperation blend_operation)
	: m_blend_operation(detail::ToVulkanBlendOperation(blend_operation))
{}

BKSGE_INLINE
BlendOperation::operator ::VkBlendOp() const
{
	return m_blend_operation;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_BLEND_OPERATION_INL_HPP
