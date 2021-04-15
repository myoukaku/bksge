/**
 *	@file	viewport.hpp
 *
 *	@brief	Viewport クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VIEWPORT_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VIEWPORT_HPP

#include <bksge/core/render/fwd/viewport_fwd.hpp>
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
class Viewport
{
public:
	explicit Viewport(bksge::Viewport const& viewport);

	operator ::VkViewport() const;

private:
	::VkViewport	m_viewport;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/viewport_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VIEWPORT_HPP
