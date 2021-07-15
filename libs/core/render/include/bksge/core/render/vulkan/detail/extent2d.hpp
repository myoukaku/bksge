/**
 *	@file	extent2d.hpp
 *
 *	@brief	Extent2D クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_EXTENT2D_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_EXTENT2D_HPP

#include <bksge/core/math/extent2.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class Extent2D : public ::VkExtent2D
{
public:
	Extent2D(bksge::Extent2<std::uint32_t> const& extent)
	{
		width  = extent.width();
		height = extent.height();
	}

	Extent2D(::VkExtent2D const& extent)
	{
		width  = extent.width;
		height = extent.height;
	}

	operator bksge::Extent2<std::uint32_t>() const
	{
		return { width, height };
	}
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_EXTENT2D_HPP
