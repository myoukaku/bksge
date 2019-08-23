/**
 *	@file	constant_buffer_descriptor.hpp
 *
 *	@brief	ConstantBufferDescriptor クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_CONSTANT_BUFFER_DESCRIPTOR_HPP
#define BKSGE_RENDER_D3D12_DETAIL_CONSTANT_BUFFER_DESCRIPTOR_HPP

#include <bksge/render/d3d12/detail/fwd/constant_buffer_descriptor_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class ConstantBufferDescriptor
{
public:
	explicit ConstantBufferDescriptor(
		Device* device,
		HLSLProgram* hlsl_program);

	~ConstantBufferDescriptor();

	void UpdateParameters(bksge::ShaderParameterMap const& shader_parameter_map);
	void SetEnable(CommandList* command_list);

private:
	using ConstantBuffers =
		std::vector<std::unique_ptr<ConstantBuffer>>;

	ConstantBuffers				m_constant_buffers;
	ComPtr<::ID3D12DescriptorHeap>		m_descriptor_heap;
	::UINT								m_cbv_descriptor_handle_incrementsize;
	::UINT								m_root_parameter_count;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/constant_buffer_descriptor_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_CONSTANT_BUFFER_DESCRIPTOR_HPP
