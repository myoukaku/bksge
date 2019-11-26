/**
 *	@file	hlsl_program.hpp
 *
 *	@brief	HlslProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_HLSL_PROGRAM_HPP
#define BKSGE_RENDER_D3D12_DETAIL_HLSL_PROGRAM_HPP

#include <bksge/render/d3d12/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/input_layout_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_texture_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_sampler_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/descriptor_heap_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/root_signature_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/root_parameters_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/descriptor_heaps_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/render/shader_stage.hpp>
#include <map>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class HlslProgram
{
public:
	explicit HlslProgram(Device* device, bksge::Shader const& shader);

	~HlslProgram();

	void SetDescriptorTables(CommandList* command_list, DescriptorHeaps* descriptor_heaps);

	void UpdateParameters(
		DescriptorHeaps* descriptor_heaps,
		ResourceCache* resource_cache,
		bksge::ShaderParameterMap const& shader_parameter_map);

	::D3D12_SHADER_BYTECODE GetShaderBytecode(bksge::ShaderStage stage) const;
	::D3D12_SHADER_BYTECODE GetVertexShaderBytecode(void) const;
	::D3D12_SHADER_BYTECODE GetPixelShaderBytecode(void) const;

	::D3D12_INPUT_LAYOUT_DESC	GetInputLayout(void) const;
	::ID3D12RootSignature*		GetRootSignature(void) const;

private:
	using HlslConstantBuffers =
		std::vector<std::unique_ptr<HlslConstantBuffer>>;
	using HlslTextures =
		std::vector<std::unique_ptr<HlslTexture>>;
	using HlslSamplers =
		std::vector<std::unique_ptr<HlslSampler>>;

private:
	HlslShaderMap					m_shader_map;
	std::unique_ptr<InputLayout>	m_input_layout;
	HlslConstantBuffers				m_hlsl_constant_buffers;
	HlslTextures					m_hlsl_textures;
	HlslSamplers					m_hlsl_samplers;
	std::unique_ptr<RootParameters>	m_root_parameters;
//	std::unique_ptr<DescriptorHeap>	m_descriptor_heap;
	std::unique_ptr<RootSignature>	m_root_signature;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/hlsl_program_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_HLSL_PROGRAM_HPP
