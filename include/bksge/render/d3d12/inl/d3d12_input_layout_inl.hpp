/**
 *	@file	d3d12_input_layout_inl.hpp
 *
 *	@brief	D3D12InputLayout クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_INPUT_LAYOUT_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_INPUT_LAYOUT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_input_layout.hpp>
//#include <bksge/render/d3d12/d3d12_input_element_format.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/d3d_common/d3dcompiler.hpp>
//#include <bksge/render/geometry.hpp>
//#include <bksge/render/vertex_layout.hpp>
//#include <bksge/render/semantic.hpp>

namespace bksge
{

namespace render
{

#if 0
BKSGE_INLINE
D3D12InputLayout::D3D12InputLayout(Geometry const& geometry)
{
	auto const& layout = geometry.vertex_layout();

	for (auto& attribute : layout.vertex_attribute_array())
	{
		::D3D12_INPUT_ELEMENT_DESC const desc =
		{
			ToSemanticName(attribute.semantic()),			// SemanticName
			0,												// SemanticIndex
			ToD3D12InputElementFormat(
				attribute.type(), attribute.element_num()),	// Format
			0,												// InputSlot
			static_cast<::UINT>(attribute.offset()),		// AlignedByteOffset
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		// InputSlotClass
			0												// InstanceDataStepRate
		};

		m_descs.push_back(desc);
	}
}
#endif

inline ::DXGI_FORMAT
GetElementDescFormat(::D3D12_SIGNATURE_PARAMETER_DESC const& param_desc)
{
	auto const mask = param_desc.Mask;
	auto const component_type = param_desc.ComponentType;

	if (mask == 1)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32_FLOAT;
		}
	}
	else if (mask <= 3)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32G32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32G32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32_FLOAT;
		}
	}
	else if (mask <= 7)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32G32B32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32G32B32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32B32_FLOAT;
		}
	}
	else if (mask <= 15)
	{
		switch (component_type)
		{
		case D3D_REGISTER_COMPONENT_UINT32:  return DXGI_FORMAT_R32G32B32A32_UINT;
		case D3D_REGISTER_COMPONENT_SINT32:  return DXGI_FORMAT_R32G32B32A32_SINT;
		case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}

BKSGE_INLINE
D3D12InputLayout::D3D12InputLayout(ComPtr<::ID3D12ShaderReflection> reflection)
{
	m_reflection = reflection;

	::D3D12_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);

	for (::UINT i = 0; i < shader_desc.InputParameters; i++)
	{
		::D3D12_SIGNATURE_PARAMETER_DESC param_desc;
		reflection->GetInputParameterDesc(i, &param_desc);

		::D3D12_INPUT_ELEMENT_DESC element_desc;
		element_desc.SemanticName         = param_desc.SemanticName;
		element_desc.SemanticIndex        = param_desc.SemanticIndex;
		element_desc.InputSlot            = 0;
		element_desc.AlignedByteOffset    = D3D12_APPEND_ALIGNED_ELEMENT;
		element_desc.InputSlotClass       = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
		element_desc.InstanceDataStepRate = 0;
		element_desc.Format               = GetElementDescFormat(param_desc);

		m_descs.push_back(element_desc);
	}
}

BKSGE_INLINE
D3D12InputLayout::operator ::D3D12_INPUT_LAYOUT_DESC() const
{
	return { m_descs.data(), static_cast<::UINT>(m_descs.size()) };
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_INPUT_LAYOUT_INL_HPP
