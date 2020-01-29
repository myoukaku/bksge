/**
 *	@file	extent2d.hpp
 *
 *	@brief	Extent2D クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_EXTENT2D_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_EXTENT2D_HPP

#include <bksge/core/math/size2.hpp>
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
class Extent2D
{
public:
	explicit Extent2D(bksge::Size2<std::uint32_t> extent2d)
	{
		m_extent2d.width  = extent2d.width();
		m_extent2d.height = extent2d.height();
	}

	operator ::VkExtent2D() const
	{
		return m_extent2d;
	}

private:
	::VkExtent2D	m_extent2d;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_EXTENT2D_HPP
