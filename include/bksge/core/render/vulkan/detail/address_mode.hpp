/**
 *	@file	address_mode.hpp
 *
 *	@brief	AddressMode クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_ADDRESS_MODE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_ADDRESS_MODE_HPP

#include <bksge/core/render/fwd/address_mode_fwd.hpp>
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
class AddressMode
{
public:
	explicit AddressMode(bksge::AddressMode address_mode);

	operator ::VkSamplerAddressMode() const;

private:
	::VkSamplerAddressMode	m_address_mode;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/address_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_ADDRESS_MODE_HPP
