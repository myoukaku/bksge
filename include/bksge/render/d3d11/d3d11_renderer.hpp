/**
 *	@file	d3d11_renderer.hpp
 *
 *	@brief	D3D11Renderer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_RENDERER_HPP
#define BKSGE_RENDER_D3D11_D3D11_RENDERER_HPP

#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_context_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_render_target_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_depth_stencil_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_texture_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_hlsl_program_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_geometry_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_sampler_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>
#include <bksge/render/fwd/render_state_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>
#include <bksge/render/fwd/sampler_fwd.hpp>
#include <bksge/render/renderer.hpp>
#include <bksge/window/fwd/window_fwd.hpp>
#include <memory>

namespace bksge
{

namespace render
{

/**
 *	@brief	D3D11レンダラー
 */
class D3D11Renderer : public Renderer
{
public:
	D3D11Renderer(void);

	virtual ~D3D11Renderer();

private:
	void Initialize(void);
	void Finalize(void);

	void VSetRenderTarget(Window const& window) override;
	void VBegin(void) override;
	void VEnd(void) override;
	void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

private:
	std::shared_ptr<D3D11HLSLProgram> GetD3D11HLSLProgram(Shader const& shader);
	std::shared_ptr<D3D11Geometry>    GetD3D11Geometry(Geometry const& geometry);
	//std::shared_ptr<D3D11Texture>     GetD3D11Texture(Texture const& texture);
	//std::shared_ptr<D3D11Sampler>     GetD3D11Sampler(Sampler const& sampler);

private:
	std::unique_ptr<DXGIFactory>       m_factory;
	std::unique_ptr<D3D11Device>        m_device;
	std::unique_ptr<D3D11DeviceContext> m_device_context;
	std::unique_ptr<DXGISwapChain>     m_swap_chain;
	std::unique_ptr<D3D11RenderTarget>  m_render_target;
	std::unique_ptr<D3D11DepthStencil>  m_depth_stencil;
	D3D11HLSLProgramMap                 m_d3d11_hlsl_program_map;
	D3D11GeometryMap                    m_d3d11_geometry_map;
	D3D11TextureMap                     m_d3d11_texture_map;
	D3D11SamplerMap                     m_d3d11_sampler_map;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_RENDERER_HPP
