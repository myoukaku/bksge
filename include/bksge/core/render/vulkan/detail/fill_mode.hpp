/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FILL_MODE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FILL_MODE_HPP

#include <bksge/core/render/fill_mode.hpp>
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
class FillMode
{
public:
	explicit FillMode(bksge::FillMode fill_mode);

	operator ::VkPolygonMode() const;

private:
	::VkPolygonMode	m_fill_mode;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/fill_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FILL_MODE_HPP
