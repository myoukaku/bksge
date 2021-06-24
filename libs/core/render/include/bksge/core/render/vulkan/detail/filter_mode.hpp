/**
 *	@file	filter_mode.hpp
 *
 *	@brief	FilterMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FILTER_MODE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FILTER_MODE_HPP

#include <bksge/core/render/fwd/filter_mode_fwd.hpp>
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
class FilterMode
{
public:
	explicit FilterMode(bksge::FilterMode filter_mode);

	operator ::VkFilter() const;

private:
	::VkFilter	m_filter_mode;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/filter_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FILTER_MODE_HPP
