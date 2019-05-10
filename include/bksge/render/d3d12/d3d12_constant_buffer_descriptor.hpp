/**
 *	@file	d3d12_constant_buffer_descriptor.hpp
 *
 *	@brief	D3D12ConstantBufferDescriptor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_CONSTANT_BUFFER_DESCRIPTOR_HPP
#define BKSGE_RENDER_D3D12_D3D12_CONSTANT_BUFFER_DESCRIPTOR_HPP

#include <bksge/render/d3d12/fwd/d3d12_constant_buffer_descriptor_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_hlsl_program_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

class D3D12ConstantBufferDescriptor
{
public:
	explicit D3D12ConstantBufferDescriptor(
		D3D12Device* device,
		D3D12HLSLProgram* hlsl_program);

	~D3D12ConstantBufferDescriptor();

	void UpdateParameters(ShaderParameterMap const& shader_parameter_map);
	void SetEnable(D3D12CommandList* command_list);

private:
	using D3D12ConstantBuffers =
		std::vector<std::unique_ptr<D3D12ConstantBuffer>>;

	D3D12ConstantBuffers				m_constant_buffers;
	ComPtr<::ID3D12DescriptorHeap>		m_descriptor_heap;
	::UINT								m_cbv_descriptor_handle_incrementsize;
	::UINT								m_root_parameter_count;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_constant_buffer_descriptor_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_CONSTANT_BUFFER_DESCRIPTOR_HPP
