/**
 *	@file	viewport_inl.hpp
 *
 *	@brief	Viewport の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VIEWPORT_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VIEWPORT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/viewport.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/viewport.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Viewport::Viewport(bksge::Viewport const& viewport)
{
	m_viewport.x        =  viewport.rect().left();
	m_viewport.y        =  viewport.rect().top() + viewport.rect().height();
	m_viewport.width    =  viewport.rect().width();
	m_viewport.height   = -viewport.rect().height();
	m_viewport.minDepth =  viewport.min_depth();
	m_viewport.maxDepth =  viewport.max_depth();
}

BKSGE_INLINE
Viewport::operator ::VkViewport() const
{
	return m_viewport;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_VIEWPORT_INL_HPP
