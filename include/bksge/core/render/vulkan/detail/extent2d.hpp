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
#include <bksge/fnd/cstdint/uint32_t.hpp>

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
	explicit Extent2D(bksge::Extent2<bksge::uint32_t> const& extent)
	{
		m_extent2d.width  = extent.width();
		m_extent2d.height = extent.height();
	}

	operator vk::Extent2D() const
	{
		return m_extent2d;
	}

private:
	vk::Extent2D	m_extent2d;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_EXTENT2D_HPP
