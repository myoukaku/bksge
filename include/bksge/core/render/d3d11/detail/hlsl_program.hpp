/**
 *	@file	hlsl_program.hpp
 *
 *	@brief	HlslProgram クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_PROGRAM_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_PROGRAM_HPP

#include <bksge/core/render/d3d11/detail/fwd/hlsl_program_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/shader_fwd.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class HlslProgram
{
public:
	explicit HlslProgram(Device* device, bksge::Shader const& shader);

	~HlslProgram();

	void Render(
		ResourcePool* resource_pool,
		Device* device,
		DeviceContext* device_context,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	// noncopyable
	HlslProgram(HlslProgram const&) = delete;
	HlslProgram& operator=(HlslProgram const&) = delete;

private:
	using HlslShaders = std::vector<HlslShaderUnique>;

	HlslShaders						m_shaders;
	ComPtr<::ID3D11InputLayout>		m_input_layout;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/hlsl_program_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_HLSL_PROGRAM_HPP
