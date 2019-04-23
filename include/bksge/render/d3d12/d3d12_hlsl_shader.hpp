/**
 *	@file	d3d12_hlsl_shader.hpp
 *
 *	@brief	D3D12HLSLShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_HLSL_SHADER_HPP
#define BKSGE_RENDER_D3D12_D3D12_HLSL_SHADER_HPP

#include <bksge/render/d3d12/fwd/d3d12_hlsl_shader_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_device_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_input_layout_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/fwd/d3d12_command_list_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/d3dcommon.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/detail/fwd/shader_parameter_map_fwd.hpp>
#include <string>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D12HLSLShaderBase
{
private:
	using D3D12ConstantBuffers =
		std::vector<std::unique_ptr<D3D12ConstantBuffer>>;

public:
	D3D12HLSLShaderBase();

	virtual ~D3D12HLSLShaderBase() = 0;

	bool Compile(D3D12Device* device, std::string const& source);
	std::unique_ptr<D3D12InputLayout> CreateInputLayout(void);
	D3D12ConstantBuffers CreateConstantBuffers(D3D12Device* device);
	::UINT GetConstantBufferCount(void) const;

	//void UpdateParameters(ShaderParameterMap const& shader_parameter_map);
	//void SetEnable(D3D12CommandList* command_list);

	::D3D12_SHADER_BYTECODE GetBytecode(void) const;

private:
	virtual const char* VGetTargetString() = 0;

private:
	ComPtr<::ID3DBlob>		m_micro_code;
};

/**
 *	@brief
 */
class D3D12HLSLVertexShader : public D3D12HLSLShaderBase
{
public:
	D3D12HLSLVertexShader();

	virtual ~D3D12HLSLVertexShader();

private:
	const char* VGetTargetString() override;

private:
};

/**
 *	@brief
 */
class D3D12HLSLPixelShader : public D3D12HLSLShaderBase
{
public:
	D3D12HLSLPixelShader();

	virtual ~D3D12HLSLPixelShader();

private:
	const char* VGetTargetString() override;

private:
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_hlsl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_HLSL_SHADER_HPP
