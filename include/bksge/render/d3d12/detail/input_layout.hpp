﻿/**
 *	@file	input_layout.hpp
 *
 *	@brief	InputLayout クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INPUT_LAYOUT_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INPUT_LAYOUT_HPP

#include <bksge/render/d3d12/detail/fwd/input_layout_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/d3d12shader.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
//#include <bksge/render/fwd/geometry_fwd.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class InputLayout
{
public:
//	explicit InputLayout(bksge::Geometry const& geometry);
	explicit InputLayout(ComPtr<::ID3D12ShaderReflection> reflection);

	operator ::D3D12_INPUT_LAYOUT_DESC() const;

private:
	std::vector<::D3D12_INPUT_ELEMENT_DESC>	m_descs;
	ComPtr<::ID3D12ShaderReflection>		m_reflection;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/input_layout_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_INPUT_LAYOUT_HPP