/**
 *	@file	comparison_function_inl.hpp
 *
 *	@brief	ComparisonFunction の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/comparison_function.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>
#include <bksge/core/render/comparison_function.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline ::VkCompareOp
ToVulkanComparisonFunction(bksge::ComparisonFunction comparison_function)
{
	switch (comparison_function)
	{
	case bksge::ComparisonFunction::kNever:			return VK_COMPARE_OP_NEVER;
	case bksge::ComparisonFunction::kLess:			return VK_COMPARE_OP_LESS;
	case bksge::ComparisonFunction::kEqual:			return VK_COMPARE_OP_EQUAL;
	case bksge::ComparisonFunction::kLessEqual:		return VK_COMPARE_OP_LESS_OR_EQUAL;
	case bksge::ComparisonFunction::kGreater:		return VK_COMPARE_OP_GREATER;
	case bksge::ComparisonFunction::kNotEqual:		return VK_COMPARE_OP_NOT_EQUAL;
	case bksge::ComparisonFunction::kGreaterEqual:	return VK_COMPARE_OP_GREATER_OR_EQUAL;
	case bksge::ComparisonFunction::kAlways:		return VK_COMPARE_OP_ALWAYS;
	}
	return VK_COMPARE_OP_NEVER;
}

}	// namespace detail

BKSGE_INLINE
ComparisonFunction::ComparisonFunction(bksge::ComparisonFunction comparison_function)
	: m_comparison_function(detail::ToVulkanComparisonFunction(comparison_function))
{}

BKSGE_INLINE
ComparisonFunction::operator ::VkCompareOp() const
{
	return m_comparison_function;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMPARISON_FUNCTION_INL_HPP
