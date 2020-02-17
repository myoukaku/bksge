/**
 *	@file	mipmap_mode.hpp
 *
 *	@brief	MipmapMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_MIPMAP_MODE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_MIPMAP_MODE_HPP

#include <bksge/core/render/fwd/mipmap_mode_fwd.hpp>
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
class MipmapMode
{
public:
	explicit MipmapMode(bksge::MipmapMode mipmap_mode);

	operator ::VkSamplerMipmapMode() const;

private:
	::VkSamplerMipmapMode	m_mipmap_mode;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/mipmap_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_MIPMAP_MODE_HPP
