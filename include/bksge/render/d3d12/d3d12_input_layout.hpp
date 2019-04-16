/**
 *	@file	d3d12_input_layout.hpp
 *
 *	@brief	D3D12InputLayout クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_INPUT_LAYOUT_HPP
#define BKSGE_RENDER_D3D12_D3D12_INPUT_LAYOUT_HPP

#include <bksge/render/d3d12/fwd/d3d12_input_layout_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>
#include <bksge/render/fwd/geometry_fwd.hpp>
#include <vector>

namespace bksge
{

namespace render
{

class D3D12InputLayout
{
public:
	explicit D3D12InputLayout(Geometry const& geometry);

	operator ::D3D12_INPUT_LAYOUT_DESC() const;

private:
	std::vector<::D3D12_INPUT_ELEMENT_DESC>	m_descs;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_input_layout_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_INPUT_LAYOUT_HPP
