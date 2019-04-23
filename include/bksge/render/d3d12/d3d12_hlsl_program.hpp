/**
 *	@file	d3d12_hlsl_program.hpp
 *
 *	@brief	D3D12HLSLProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_HLSL_PROGRAM_HPP
#define BKSGE_RENDER_D3D12_D3D12_HLSL_PROGRAM_HPP

#include <bksge/render/d3d12/fwd/d3d12_hlsl_program_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_hlsl_shader_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_input_layout_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_root_signature_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/shader_stage.hpp>
#include <bksge/render/detail/fwd/shader_parameter_map_fwd.hpp>
#include <map>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

class D3D12HLSLProgram
{
public:
	explicit D3D12HLSLProgram(D3D12Device* device, Shader const& shader);

	~D3D12HLSLProgram();

	void UpdateParameters(ShaderParameterMap const& shader_parameter_map);
	void SetEnable(D3D12CommandList* command_list);

	::D3D12_SHADER_BYTECODE GetShaderBytecode(ShaderStage stage) const;
	::D3D12_SHADER_BYTECODE GetVertexShaderBytecode(void) const;
	::D3D12_SHADER_BYTECODE GetPixelShaderBytecode(void) const;

	::D3D12_INPUT_LAYOUT_DESC	GetInputLayout(void) const;
	::ID3D12RootSignature*		GetRootSignature(void) const;

private:
	using D3D12ConstantBuffers =
		std::vector<std::unique_ptr<D3D12ConstantBuffer>>;

	D3D12HLSLShaderMap					m_shader_map;
	std::unique_ptr<D3D12InputLayout>	m_input_layout;
	D3D12ConstantBuffers				m_constant_buffers;
	ComPtr<::ID3D12DescriptorHeap>		m_descriptor_heap;
	::UINT								m_cbv_descriptor_handle_incrementsize;
	std::unique_ptr<D3D12RootSignature>	m_root_signature;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_hlsl_program_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_HLSL_PROGRAM_HPP
