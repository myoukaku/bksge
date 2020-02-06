/**
 *	@file	color_write_flag.hpp
 *
 *	@brief	ColorWriteFlag クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_COLOR_WRITE_FLAG_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_COLOR_WRITE_FLAG_HPP

#include <bksge/core/render/fwd/color_write_flag_fwd.hpp>
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
class ColorWriteFlag
{
public:
	explicit ColorWriteFlag(bksge::ColorWriteFlag color_write_flag);

	operator ::VkColorComponentFlags() const;

private:
	::VkColorComponentFlags	m_color_write_flag;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/color_write_flag_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COLOR_WRITE_FLAG_HPP
