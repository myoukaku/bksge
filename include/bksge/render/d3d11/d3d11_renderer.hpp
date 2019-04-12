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
#include <bksge/render/d3d11/fwd/d3d11_texture_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_hlsl_program_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_geometry_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_sampler_fwd.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/fwd/shader_fwd.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
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

	std::shared_ptr<D3D11HLSLProgram> GetD3D11HLSLProgram(Shader const& shader);
	std::shared_ptr<D3D11Geometry>    GetD3D11Geometry(Geometry const& geometry);
	std::shared_ptr<D3D11Texture>     GetD3D11Texture(Texture const& texture);
	std::shared_ptr<D3D11Sampler>     GetD3D11Sampler(Sampler const& sampler);

	ComPtr<::ID3D11Buffer> CreateBuffer(::D3D11_BUFFER_DESC const& desc, ::D3D11_SUBRESOURCE_DATA const& subsource_data);
	ComPtr<::ID3D11SamplerState> CreateSamplerState(::D3D11_SAMPLER_DESC const& desc);
	ComPtr<::ID3D11Texture2D> CreateTexture2D(::D3D11_TEXTURE2D_DESC const& desc, ::D3D11_SUBRESOURCE_DATA const& init_data);
	ComPtr<::ID3D11VertexShader> CreateVertexShader(::ID3DBlob* micro_code);
	ComPtr<::ID3D11PixelShader> CreatePixelShader(::ID3DBlob* micro_code);
	ComPtr<::ID3D11ShaderResourceView> CreateShaderResourceView(::ID3D11Resource* resource, ::D3D11_SHADER_RESOURCE_VIEW_DESC const& desc);
    ComPtr<::ID3D11InputLayout> CreateInputLayout(
		::D3D11_INPUT_ELEMENT_DESC const* desc,
		::UINT num_elements,
		void const* bytecode,
		::SIZE_T bytecode_length);

	void SetIndexBuffer(::ID3D11Buffer* index_buffer, ::DXGI_FORMAT format, ::UINT offset);
	void SetVertexBuffers(
		::UINT start_slot,
		::UINT num_buffers,
		::ID3D11Buffer* const* vertex_buffers,
		::UINT const* strides,
		::UINT const* offsets);
	void VSSetShader(::ID3D11VertexShader* vertex_shader);
	void PSSetShader(::ID3D11PixelShader* pixel_shader);
	void SetInputLayout(::ID3D11InputLayout* input_layout);
	void PSSetSamplers(::UINT start_slot, ::UINT num_samplers, ::ID3D11SamplerState* const* samplers);
	void PSSetShaderResources(::UINT start_slot, ::UINT num_views, ::ID3D11ShaderResourceView* const* shader_resource_views);
	void SetPrimitiveTopology(::D3D11_PRIMITIVE_TOPOLOGY topology);

	void Draw(::UINT vertex_count, ::UINT start_vertex_location);
	void DrawIndexed(::UINT index_count, ::UINT start_index_location, ::INT base_vertex_location);

private:
	void CreateDevice(void);
	void Finalize(void);

	virtual void VSetRenderTarget(Window const& window) override;
	virtual void VBegin(void) override;
	virtual void VEnd(void) override;
	virtual void VClear(ClearFlag clear_flag, Color4f const& clear_color) override;
	virtual void VRender(Geometry const& geometry, Shader const& shader) override;

private:
	::D3D_DRIVER_TYPE                m_driver_type   = ::D3D_DRIVER_TYPE_NULL;
	::D3D_FEATURE_LEVEL              m_feature_level = ::D3D_FEATURE_LEVEL_11_0;
	ComPtr<::ID3D11Device>           m_device;
	ComPtr<::ID3D11DeviceContext>    m_device_context;
	ComPtr<::IDXGISwapChain>         m_swap_chain;
	ComPtr<::ID3D11Texture2D>        m_depth_stencil;
	ComPtr<::ID3D11DepthStencilView> m_depth_stencil_view;
	ComPtr<::ID3D11RenderTargetView> m_render_target_view;
	D3D11HLSLProgramMap              m_d3d11_hlsl_program_map;
	D3D11GeometryMap                 m_d3d11_geometry_map;
	D3D11TextureMap                  m_d3d11_texture_map;
	D3D11SamplerMap                  m_d3d11_sampler_map;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_renderer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_RENDERER_HPP
