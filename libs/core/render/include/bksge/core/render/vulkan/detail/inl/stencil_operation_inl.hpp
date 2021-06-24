/**
 *	@file	stencil_operation_inl.hpp
 *
 *	@brief	StencilOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_STENCIL_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_STENCIL_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/stencil_operation.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/stencil_operation.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkStencilOp
ToVulkanStencilOperation(bksge::StencilOperation stencil_operation)
{
	switch (stencil_operation)
	{
	case bksge::StencilOperation::kKeep:         return VK_STENCIL_OP_KEEP;
	case bksge::StencilOperation::kZero:         return VK_STENCIL_OP_ZERO;
	case bksge::StencilOperation::kReplace:      return VK_STENCIL_OP_REPLACE;
	case bksge::StencilOperation::kIncrSaturate: return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
	case bksge::StencilOperation::kDecrSaturate: return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
	case bksge::StencilOperation::kInvert:       return VK_STENCIL_OP_INVERT;
	case bksge::StencilOperation::kIncr:         return VK_STENCIL_OP_INCREMENT_AND_WRAP;
	case bksge::StencilOperation::kDecr:         return VK_STENCIL_OP_DECREMENT_AND_WRAP;
	}
	return VK_STENCIL_OP_KEEP;
}

}	// namespace detail

BKSGE_INLINE
StencilOperation::StencilOperation(bksge::StencilOperation stencil_operation)
	: m_stencil_operation(detail::ToVulkanStencilOperation(stencil_operation))
{}

BKSGE_INLINE
StencilOperation::operator ::VkStencilOp() const
{
	return m_stencil_operation;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_STENCIL_OPERATION_INL_HPP
