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
#include <bksge/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/render_target_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/depth_stencil_fwd.hpp>
//#include <bksge/render/d3d11/detail/fwd/texture_fwd.hpp>
//#include <bksge/render/d3d11/detail/fwd/hlsl_program_fwd.hpp>
//#include <bksge/render/d3d11/detail/fwd/geometry_fwd.hpp>
//#include <bksge/render/d3d11/detail/fwd/sampler_fwd.hpp>
#include <bksge/render/d3d11/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_factory_fwd.hpp>
#include <bksge/render/dxgi/fwd/dxgi_swap_chain_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/render/fwd/render_state_fwd.hpp>
//#include <bksge/render/fwd/texture_fwd.hpp>
//#include <bksge/render/fwd/sampler_fwd.hpp>
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
	bool VRender(
		Geometry const& geometry,
		Shader const& shader,
		ShaderParameterMap const& shader_parameter_map,
		RenderState const& render_state) override;

private:
	std::unique_ptr<DXGIFactory>          m_factory;
	std::unique_ptr<d3d11::Device>        m_device;
	std::unique_ptr<d3d11::DeviceContext> m_device_context;
	std::unique_ptr<DXGISwapChain>        m_swap_chain;
	std::unique_ptr<d3d11::RenderTarget>  m_render_target;
	std::unique_ptr<d3d11::DepthStencil>  m_depth_stencil;
	std::unique_ptr<d3d11::ResourceCache> m_resource_cache;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_RENDERER_HPP
