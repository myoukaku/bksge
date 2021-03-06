﻿/**
 *	@file	root_parameters.hpp
 *
 *	@brief	RootParameters クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_ROOT_PARAMETERS_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_ROOT_PARAMETERS_HPP

#include <bksge/core/render/d3d12/detail/fwd/root_parameters_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class RootParameters
{
public:
	explicit RootParameters(HlslShaderMap const& shader_map);

	~RootParameters();

	::UINT GetSize(void) const;

	::D3D12_ROOT_PARAMETER1 const* GetData(void) const;

	::D3D12_ROOT_PARAMETER_TYPE GetType(::UINT index) const;

	::D3D12_DESCRIPTOR_RANGE_TYPE GetDescriptorRangeType(::UINT index) const;

private:
	// noncopyable
	RootParameters(RootParameters const&) = delete;
	RootParameters& operator=(RootParameters const&) = delete;

private:
	bksge::vector<::D3D12_ROOT_PARAMETER1> m_root_parameters;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/root_parameters_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_ROOT_PARAMETERS_HPP
