/**
 *	@file	stencil_operation.hpp
 *
 *	@brief	StencilOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_STENCIL_OPERATION_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_STENCIL_OPERATION_HPP

#include <bksge/core/render/stencil_operation.hpp>
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
class StencilOperation
{
public:
	explicit StencilOperation(bksge::StencilOperation stencil_operation);

	operator ::VkStencilOp() const;

private:
	::VkStencilOp	m_stencil_operation;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/stencil_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_STENCIL_OPERATION_HPP
