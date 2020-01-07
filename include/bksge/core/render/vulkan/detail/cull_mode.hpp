/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_CULL_MODE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_CULL_MODE_HPP

#include <bksge/core/render/cull_mode.hpp>
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
class CullMode
{
public:
	explicit CullMode(bksge::CullMode cull_mode);

	operator ::VkCullModeFlags() const;

private:
	::VkCullModeFlags	m_cull_mode;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_CULL_MODE_HPP
