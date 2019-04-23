/**
 *	@file	d3d11_device_context_inl.hpp
 *
 *	@brief	D3D11DeviceContext の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_DEVICE_CONTEXT_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_DEVICE_CONTEXT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_device_context.hpp>
#include <bksge/render/d3d11/d3d11_device.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11DeviceContext::D3D11DeviceContext(D3D11Device* device)
{
	m_device_context = device->GetImmediateContext();
}

BKSGE_INLINE
D3D11DeviceContext::~D3D11DeviceContext()
{
}

BKSGE_INLINE void
D3D11DeviceContext::IASetIndexBuffer(
	::ID3D11Buffer* index_buffer,
	::DXGI_FORMAT format,
	::UINT offset)
{
	m_device_context->IASetIndexBuffer(index_buffer, format, offset);
}

BKSGE_INLINE void
D3D11DeviceContext::IASetVertexBuffers(
	::UINT start_slot,
	::UINT num_buffers,
	::ID3D11Buffer* const* vertex_buffers,
	::UINT const* strides,
	::UINT const* offsets)
{
	m_device_context->IASetVertexBuffers(
		start_slot,
		num_buffers,
		vertex_buffers,
		strides,
		offsets);
}

BKSGE_INLINE void
D3D11DeviceContext::IASetInputLayout(::ID3D11InputLayout* input_layout)
{
	m_device_context->IASetInputLayout(input_layout);
}

BKSGE_INLINE void
D3D11DeviceContext::IASetPrimitiveTopology(::D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_device_context->IASetPrimitiveTopology(topology);
}

BKSGE_INLINE void
D3D11DeviceContext::VSSetShader(::ID3D11VertexShader* vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader, nullptr, 0u);
}

BKSGE_INLINE void
D3D11DeviceContext::VSSetConstantBuffers(
	::UINT         start_slot,
	::UINT         num_buffers,
	::ID3D11Buffer* const* constant_buffers)
{
	m_device_context->VSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
}

BKSGE_INLINE void
D3D11DeviceContext::PSSetShader(::ID3D11PixelShader* pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader, nullptr, 0u);
}

BKSGE_INLINE void
D3D11DeviceContext::PSSetConstantBuffers(
	::UINT         start_slot,
	::UINT         num_buffers,
	::ID3D11Buffer* const* constant_buffers)
{
	m_device_context->PSSetConstantBuffers(start_slot, num_buffers, constant_buffers);
}

BKSGE_INLINE void
D3D11DeviceContext::PSSetSamplers(
	::UINT start_slot,
	::UINT num_samplers,
	::ID3D11SamplerState* const* samplers)
{
	m_device_context->PSSetSamplers(start_slot, num_samplers, samplers);
}

BKSGE_INLINE void
D3D11DeviceContext::PSSetShaderResources(
	::UINT start_slot,
	::UINT num_views,
	::ID3D11ShaderResourceView* const* shader_resource_views)
{
	m_device_context->PSSetShaderResources(start_slot, num_views, shader_resource_views);
}

BKSGE_INLINE void
D3D11DeviceContext::RSSetViewports(
	::UINT                 num_viewports,
	const ::D3D11_VIEWPORT* viewports)
{
	m_device_context->RSSetViewports(num_viewports, viewports);
}

BKSGE_INLINE void
D3D11DeviceContext::RSSetState(
	::ID3D11RasterizerState* rasterizer_state)
{
	m_device_context->RSSetState(rasterizer_state);
}

BKSGE_INLINE void
D3D11DeviceContext::OMSetRenderTargets(
	::UINT                           num_views,
	::ID3D11RenderTargetView* const* render_target_views,
	::ID3D11DepthStencilView*        depth_stencil_view)
{
	m_device_context->OMSetRenderTargets(num_views, render_target_views, depth_stencil_view);
}

BKSGE_INLINE void
D3D11DeviceContext::UpdateSubresource(
	::ID3D11Resource*  dst_resource,
	::UINT             dst_subresource,
	::D3D11_BOX const* dst_box,
	void        const* src_data,
	::UINT             src_row_pitch,
	::UINT             src_depth_pitch)
{
	m_device_context->UpdateSubresource(
		dst_resource,
		dst_subresource,
		dst_box,
		src_data,
		src_row_pitch,
		src_depth_pitch);
}

BKSGE_INLINE void
D3D11DeviceContext::ClearState(void)
{
	m_device_context->ClearState();
}

BKSGE_INLINE void
D3D11DeviceContext::ClearRenderTargetView(
	::ID3D11RenderTargetView* render_target_view,
	::FLOAT const*            color_rgba)
{
	m_device_context->ClearRenderTargetView(render_target_view, color_rgba);
}

BKSGE_INLINE void
D3D11DeviceContext::ClearDepthStencilView(
	::ID3D11DepthStencilView* depth_stencil_view,
	::UINT                    clear_flags,
	::FLOAT                   depth,
	::UINT8                   stencil)
{
	m_device_context->ClearDepthStencilView(depth_stencil_view, clear_flags, depth, stencil);
}

BKSGE_INLINE void
D3D11DeviceContext::Draw(
	::UINT vertex_count,
	::UINT start_vertex_location)
{
	m_device_context->Draw(vertex_count, start_vertex_location);
}

BKSGE_INLINE void
D3D11DeviceContext::DrawIndexed(
	::UINT index_count,
	::UINT start_index_location,
	::INT  base_vertex_location)
{
	m_device_context->DrawIndexed(index_count, start_index_location, base_vertex_location);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_DEVICE_CONTEXT_INL_HPP
