﻿/**
 *	@file	device_context.hpp
 *
 *	@brief	DeviceContext クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_DEVICE_CONTEXT_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_DEVICE_CONTEXT_HPP

#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class DeviceContext
{
public:
	explicit DeviceContext(Device* device);

	~DeviceContext();

	void IASetIndexBuffer(
		::ID3D11Buffer* index_buffer,
		::DXGI_FORMAT format,
		::UINT offset);

	void IASetVertexBuffers(
		::UINT start_slot,
		::UINT num_buffers,
		::ID3D11Buffer* const* vertex_buffers,
		::UINT const* strides,
		::UINT const* offsets);

	void IASetInputLayout(::ID3D11InputLayout* input_layout);

	void IASetPrimitiveTopology(
		::D3D11_PRIMITIVE_TOPOLOGY topology);

	void VSSetShader(::ID3D11VertexShader* vertex_shader);

	void VSSetConstantBuffers(
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers);

	void VSSetSamplers(
		::UINT start_slot,
		::UINT num_samplers,
		::ID3D11SamplerState* const* samplers);

	void VSSetShaderResources(
		::UINT start_slot,
		::UINT num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views);

	void PSSetShader(::ID3D11PixelShader* pixel_shader);

	void PSSetConstantBuffers(
		::UINT         start_slot,
		::UINT         num_buffers,
		::ID3D11Buffer* const* constant_buffers);

	void PSSetSamplers(
		::UINT start_slot,
		::UINT num_samplers,
		::ID3D11SamplerState* const* samplers);

	void PSSetShaderResources(
		::UINT start_slot,
		::UINT num_views,
		::ID3D11ShaderResourceView* const* shader_resource_views);

	void RSSetViewports(
		::UINT                  num_viewports,
		::D3D11_VIEWPORT const* viewports);

	void RSSetScissorRects(
		UINT              num_rects,
		D3D11_RECT const* rects);

	void RSSetState(
		::ID3D11RasterizerState* rasterizer_state);

	void OMSetRenderTargets(
		::UINT                           num_views,
		::ID3D11RenderTargetView* const* render_target_views,
		::ID3D11DepthStencilView*        depth_stencil_view);

	void OMSetBlendState(
		::ID3D11BlendState* blend_state,
		::FLOAT const       blend_factor[4],
		::UINT              sample_mask);

	void OMSetDepthStencilState(
		::ID3D11DepthStencilState* depth_stencil_state,
		::UINT                     stencil_ref);

	void UpdateSubresource(
		::ID3D11Resource*  dst_resource,
		::UINT             dst_subresource,
		::D3D11_BOX const* dst_box,
		void        const* src_data,
		::UINT             src_row_pitch,
		::UINT             src_depth_pitch);

	void ClearState(void);

	void ClearRenderTargetView(
		::ID3D11RenderTargetView* render_target_view,
		::FLOAT const*            color_rgba);

	void ClearDepthStencilView(
		::ID3D11DepthStencilView* depth_stencil_view,
		::UINT                    clear_flags,
		::FLOAT                   depth,
		::UINT8                   stencil);

	void Draw(
		::UINT vertex_count,
		::UINT start_vertex_location);

	void DrawIndexed(
		::UINT index_count,
		::UINT start_index_location,
		::INT  base_vertex_location);

private:
	// noncopyable
	DeviceContext(DeviceContext const&) = delete;
	DeviceContext& operator=(DeviceContext const&) = delete;

private:
	ComPtr<ID3D11DeviceContextN>    m_device_context;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/device_context_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_DEVICE_CONTEXT_HPP
