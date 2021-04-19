/**
 *	@file	uniform_buffer.hpp
 *
 *	@brief	UniformBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/uniform_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class UniformBuffer
{
public:
	explicit UniformBuffer(
		vulkan::DeviceSharedPtr const& device,
		::VkDeviceSize                 size);

	~UniformBuffer();

	vulkan::Buffer const& buffer(void) const;

	bksge::uint8_t* mapped_buffer(void) const;

	bksge::size_t Allocate(bksge::size_t size);

	void BeginFrame(void);

private:
	// noncopyable
	UniformBuffer(UniformBuffer const&) = delete;
	UniformBuffer& operator=(UniformBuffer const&) = delete;

private:
	bksge::unique_ptr<vulkan::Buffer>	m_buffer;
	bksge::uint8_t*						m_mapped_buffer = nullptr;
	bksge::size_t						m_offset = 0;
	bksge::size_t						m_offset_alignment = 0;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/uniform_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_UNIFORM_BUFFER_HPP
