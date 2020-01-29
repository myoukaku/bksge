/**
 *	@file	texture_format.hpp
 *
 *	@brief	TextureFormat クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_TEXTURE_FORMAT_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_TEXTURE_FORMAT_HPP

#include <bksge/core/render/fwd/texture_format_fwd.hpp>
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
class TextureFormat
{
public:
	explicit TextureFormat(bksge::TextureFormat texture_format);

	operator ::VkFormat() const;

private:
	::VkFormat	m_format;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/texture_format_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_TEXTURE_FORMAT_HPP
