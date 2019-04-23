﻿/**
 *	@file	d3d11_constant_buffer_inl.hpp
 *
 *	@brief	D3D11ConstantBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_CONSTANT_BUFFER_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_CONSTANT_BUFFER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_constant_buffer.hpp>
#include <bksge/render/d3d11/d3d11_device.hpp>
#include <bksge/render/d3d11/d3d11_device_context.hpp>
#include <bksge/render/d3d_common/d3d11shader.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/detail/shader_parameter_map.hpp>
#include <string>
#include <vector>
#include <cstring>	// memcpy

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11ConstantBuffer::D3D11ConstantBuffer(
	D3D11Device* device,
	::ID3D11ShaderReflectionConstantBuffer* constant_buffer)
{
	::D3D11_SHADER_BUFFER_DESC desc;
	constant_buffer->GetDesc(&desc);

	m_name = desc.Name;
	m_size = desc.Size;

	m_buffer_data.resize(m_size);

	::D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth      = desc.Size;
	buffer_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	m_buffer = device->CreateBuffer(buffer_desc, nullptr);

	for (::UINT i = 0; i < desc.Variables; ++i)
	{
		auto variable = constant_buffer->GetVariableByIndex(i);
		::D3D11_SHADER_VARIABLE_DESC variable_desc;
		variable->GetDesc(&variable_desc);

		if (variable_desc.uFlags & D3D_SVF_USED)
		{
			Variable v;
			v.m_name         = variable_desc.Name;
			v.m_start_offset = variable_desc.StartOffset;
			v.m_size         = variable_desc.Size;
			m_variables.push_back(v);
		}
	}
}

BKSGE_INLINE
D3D11ConstantBuffer::~D3D11ConstantBuffer()
{
}

BKSGE_INLINE void
D3D11ConstantBuffer::LoadParameters(
	D3D11DeviceContext* device_context,
	ShaderParameterMap const& shader_parameter_map)
{
	auto dst = m_buffer_data.data();
	for (auto&& variable : m_variables)
	{
		auto param = shader_parameter_map[variable.m_name];
		if (param)
		{
			auto src = param->data();
			std::memcpy(
				dst + variable.m_start_offset,
				src,
				variable.m_size);
		}
	}

	device_context->UpdateSubresource(
		m_buffer.Get(), 0, nullptr, dst, 0, 0);
}

BKSGE_INLINE ComPtr<::ID3D11Buffer> const&
D3D11ConstantBuffer::buffer(void) const
{
	return m_buffer;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_CONSTANT_BUFFER_INL_HPP
