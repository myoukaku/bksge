/**
 *	@file	hlsl_shader.hpp
 *
 *	@brief	HLSLShader クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_HLSL_SHADER_HPP
#define BKSGE_RENDER_D3D12_DETAIL_HLSL_SHADER_HPP

#include <bksge/render/d3d12/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/input_layout_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/command_list_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/d3dcommon.hpp>
#include <bksge/render/d3d_common/d3d12shader.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <string>
#include <memory>
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
class HLSLShaderBase
{
private:
	using ConstantBuffers =
		std::vector<std::unique_ptr<ConstantBuffer>>;

public:
	HLSLShaderBase();

	virtual ~HLSLShaderBase() = 0;

	bool Compile(Device* device, std::string const& source);
	std::unique_ptr<InputLayout> CreateInputLayout(void);
	ConstantBuffers CreateConstantBuffers(Device* device);
	::UINT GetConstantBufferCount(void) const;

	::D3D12_SHADER_BYTECODE GetBytecode(void) const;

private:
	virtual const char* VGetTargetString() = 0;

private:
	ComPtr<::ID3DBlob>					m_micro_code;
	ComPtr<::ID3D12ShaderReflection>	m_reflection;
};

/**
 *	@brief
 */
class HLSLVertexShader : public HLSLShaderBase
{
public:
	HLSLVertexShader();

	virtual ~HLSLVertexShader();

private:
	const char* VGetTargetString() override;

private:
};

/**
 *	@brief
 */
class HLSLPixelShader : public HLSLShaderBase
{
public:
	HLSLPixelShader();

	virtual ~HLSLPixelShader();

private:
	const char* VGetTargetString() override;

private:
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/hlsl_shader_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_HLSL_SHADER_HPP
