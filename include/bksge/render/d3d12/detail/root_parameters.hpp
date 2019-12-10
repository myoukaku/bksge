/**
 *	@file	root_parameters.hpp
 *
 *	@brief	RootParameters クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_ROOT_PARAMETERS_HPP
#define BKSGE_RENDER_D3D12_DETAIL_ROOT_PARAMETERS_HPP

#include <bksge/render/d3d12/detail/fwd/root_parameters_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/hlsl_shader_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <vector>

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
	std::vector<::D3D12_ROOT_PARAMETER1> m_root_parameters;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/root_parameters_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_ROOT_PARAMETERS_HPP
