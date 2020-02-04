/**
 *	@file	border_color.hpp
 *
 *	@brief	BorderColor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BORDER_COLOR_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BORDER_COLOR_HPP

#include <bksge/core/render/fwd/border_color_fwd.hpp>
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
class BorderColor
{
public:
	explicit BorderColor(bksge::BorderColor border_color);

	operator ::VkBorderColor() const;

private:
	::VkBorderColor	m_border_color;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/border_color_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BORDER_COLOR_HPP
