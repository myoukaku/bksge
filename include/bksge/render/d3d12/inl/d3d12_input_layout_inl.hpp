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
#include <bksge/render/d3d12/d3d12_input_element_format.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/geometry.hpp>
#include <bksge/render/vertex_layout.hpp>
#include <bksge/render/semantic.hpp>

namespace bksge
{

namespace render
{

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

BKSGE_INLINE
D3D12InputLayout::operator ::D3D12_INPUT_LAYOUT_DESC() const
{
	return { m_descs.data(), static_cast<::UINT>(m_descs.size()) };
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_INPUT_LAYOUT_INL_HPP
