/**
 *	@file	sampler.hpp
 *
 *	@brief	Sampler クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SAMPLER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SAMPLER_HPP

#include <bksge/core/render/vulkan/detail/fwd/sampler_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/sampler_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Sampler
{
public:
	explicit Sampler(
		vulkan::DeviceSharedPtr const& device,
		bksge::Sampler const& sampler);

	~Sampler();

	operator ::VkSampler() const;

private:
	// noncopyable
	Sampler(Sampler const&) = delete;
	Sampler& operator=(Sampler const&) = delete;

private:
	vulkan::DeviceSharedPtr		m_device;
	::VkSampler					m_sampler = VK_NULL_HANDLE;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/sampler_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SAMPLER_HPP
