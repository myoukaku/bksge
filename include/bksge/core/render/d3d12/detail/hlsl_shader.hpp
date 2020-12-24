/**
 *	@file	hlsl_shader.hpp
 *
 *	@brief	HlslShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_SHADER_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_SHADER_HPP

#include <bksge/core/render/d3d12/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/input_layout_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/hlsl_constant_buffer_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/hlsl_texture_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/hlsl_sampler_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/d3dcommon.hpp>
#include <bksge/core/render/d3d_common/d3d12shader.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/string/string.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

/**
 *	@brief
 */
class HlslShaderBase
{
private:
	using HlslConstantBuffers =
		std::vector<bksge::unique_ptr<HlslConstantBuffer>>;
	using HlslTextures =
		std::vector<bksge::unique_ptr<HlslTexture>>;
	using HlslSamplers =
		std::vector<bksge::unique_ptr<HlslSampler>>;

public:
	HlslShaderBase();

	virtual ~HlslShaderBase() = 0;

	bool Compile(Device* device, bksge::string const& source);
	bksge::unique_ptr<InputLayout> CreateInputLayout(void);
	void CreateHlslConstantBuffers(/*Device* device, */HlslConstantBuffers* hlsl_constant_buffers);
	void CreateHlslTextures(HlslTextures* hlsl_textures);
	void CreateHlslSamplers(HlslSamplers* hlsl_samplers);

	::D3D12_SHADER_BYTECODE GetBytecode(void) const;

	std::vector<::D3D12_DESCRIPTOR_RANGE1> const& GetDescriptorRanges(void) const;
	std::vector<::D3D12_DESCRIPTOR_RANGE1> const& GetSamplerDescriptorRanges(void) const;

private:
	virtual const char* VGetTargetString() = 0;

	void CreateDescriptorRanges(void);

private:
	// noncopyable
	HlslShaderBase(HlslShaderBase const&) = delete;
	HlslShaderBase& operator=(HlslShaderBase const&) = delete;

private:
	ComPtr<::ID3DBlob>							m_micro_code;
	ComPtr<::ID3D12ShaderReflection>			m_reflection;
	std::vector<::D3D12_DESCRIPTOR_RANGE1>	m_descriptor_ranges;
	std::vector<::D3D12_DESCRIPTOR_RANGE1>	m_sampler_descriptor_ranges;
};

/**
 *	@brief
 */
class HlslVertexShader : public HlslShaderBase
{
public:
	HlslVertexShader();

	virtual ~HlslVertexShader();

private:
	const char* VGetTargetString() override;

private:
};

/**
 *	@brief
 */
class HlslPixelShader : public HlslShaderBase
{
public:
	HlslPixelShader();

	virtual ~HlslPixelShader();

private:
	const char* VGetTargetString() override;

private:
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/hlsl_shader_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_SHADER_HPP
