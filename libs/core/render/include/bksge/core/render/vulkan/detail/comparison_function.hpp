/**
 *	@file	comparison_function.hpp
 *
 *	@brief	ComparisonFunction クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_COMPARISON_FUNCTION_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_COMPARISON_FUNCTION_HPP

#include <bksge/core/render/comparison_function.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class ComparisonFunction
{
public:
	explicit ComparisonFunction(bksge::ComparisonFunction comparison_function);

	operator ::VkCompareOp() const;

private:
	::VkCompareOp	m_comparison_function;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/comparison_function_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMPARISON_FUNCTION_HPP
