/**
 *	@file	logic_operation_inl.hpp
 *
 *	@brief	LogicOperation の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_LOGIC_OPERATION_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_LOGIC_OPERATION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/logic_operation.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/logic_operation.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkLogicOp
ToVulkanBlendOperation(bksge::LogicOperation logic_operation)
{
	switch (logic_operation)
	{
	case bksge::LogicOperation::kClear:        return VK_LOGIC_OP_CLEAR;
	case bksge::LogicOperation::kSet:          return VK_LOGIC_OP_SET;
	case bksge::LogicOperation::kCopy:         return VK_LOGIC_OP_COPY;
	case bksge::LogicOperation::kCopyInverted: return VK_LOGIC_OP_COPY_INVERTED;
	case bksge::LogicOperation::kNoop:         return VK_LOGIC_OP_NO_OP;
	case bksge::LogicOperation::kInvert:       return VK_LOGIC_OP_INVERT;
	case bksge::LogicOperation::kAnd:          return VK_LOGIC_OP_AND;
	case bksge::LogicOperation::kNand:         return VK_LOGIC_OP_NAND;
	case bksge::LogicOperation::kOr:           return VK_LOGIC_OP_OR;
	case bksge::LogicOperation::kNor:          return VK_LOGIC_OP_NOR;
	case bksge::LogicOperation::kXor:          return VK_LOGIC_OP_XOR;
	case bksge::LogicOperation::kEquiv:        return VK_LOGIC_OP_EQUIVALENT;
	case bksge::LogicOperation::kAndReverse:   return VK_LOGIC_OP_AND_REVERSE;
	case bksge::LogicOperation::kAndInverted:  return VK_LOGIC_OP_AND_INVERTED;
	case bksge::LogicOperation::kOrReverse:    return VK_LOGIC_OP_OR_REVERSE;
	case bksge::LogicOperation::kOrInverted:   return VK_LOGIC_OP_OR_INVERTED;
	}
	return VK_LOGIC_OP_COPY;
}

}	// namespace detail

BKSGE_INLINE
LogicOperation::LogicOperation(bksge::LogicOperation logic_operation)
	: m_logic_operation(detail::ToVulkanBlendOperation(logic_operation))
{}

BKSGE_INLINE
LogicOperation::operator ::VkLogicOp() const
{
	return m_logic_operation;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_LOGIC_OPERATION_INL_HPP
