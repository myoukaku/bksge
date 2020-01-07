/**
 *	@file	blend_operation.hpp
 *
 *	@brief	BlendOperation クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_OPERATION_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_OPERATION_HPP

#include <bksge/core/render/fwd/blend_operation_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan_h.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class BlendOperation
{
public:
	explicit BlendOperation(bksge::BlendOperation blend_operation);

	operator ::VkBlendOp() const;

private:
	::VkBlendOp	m_blend_operation;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/blend_operation_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BLEND_OPERATION_HPP
