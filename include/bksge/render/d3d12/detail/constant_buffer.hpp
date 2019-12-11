/**
 *	@file	constant_buffer.hpp
 *
 *	@brief	ConstantBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_CONSTANT_BUFFER_HPP
#define BKSGE_RENDER_D3D12_DETAIL_CONSTANT_BUFFER_HPP

#include <bksge/render/d3d12/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
//#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <cstdint>
#include <cstddef>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class ConstantBuffer
{
public:
	explicit ConstantBuffer(
		Device* device,
		::UINT	size);

	~ConstantBuffer();

	struct Subresource
	{
	public:
		Subresource(
			::UINT						  size,
			::D3D12_GPU_VIRTUAL_ADDRESS	  gpu_virtual_address,
			std::uint8_t*				  mapped_resource);

		~Subresource();

		void Update(std::vector<std::uint8_t> const& buffer);

		void CreateView(Device* device, ::D3D12_CPU_DESCRIPTOR_HANDLE dest);

	private:
		::UINT						m_size;
		::D3D12_GPU_VIRTUAL_ADDRESS	m_gpu_virtual_address;
		std::uint8_t*				m_mapped_resource;
	};

	Subresource AssignSubresource(std::size_t size);

private:
	::UINT GetSizeInBytes(void) const;

private:
	ComPtr<::ID3D12Resource>	m_resource;
	std::uint8_t*				m_mapped_resource = nullptr;
	std::size_t					m_offset = 0;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/constant_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_CONSTANT_BUFFER_HPP
