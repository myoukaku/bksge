/**
 *	@file	root_parameters_inl.hpp
 *
 *	@brief	RootParameters クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_ROOT_PARAMETERS_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_ROOT_PARAMETERS_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/root_parameters.hpp>
#include <bksge/render/d3d12/detail/hlsl_shader.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_SHADER_VISIBILITY
ToShaderVisibility(bksge::ShaderStage stage)
{
	switch (stage)
	{
	case bksge::ShaderStage::kVertex:                 return D3D12_SHADER_VISIBILITY_VERTEX;
	case bksge::ShaderStage::kTessellationControl:    return D3D12_SHADER_VISIBILITY_HULL;
	case bksge::ShaderStage::kTessellationEvaluation: return D3D12_SHADER_VISIBILITY_DOMAIN;
	case bksge::ShaderStage::kGeometry:               return D3D12_SHADER_VISIBILITY_GEOMETRY;
	case bksge::ShaderStage::kFragment:               return D3D12_SHADER_VISIBILITY_PIXEL;
	}
	return D3D12_SHADER_VISIBILITY_ALL;
}

}	// namespace detail

BKSGE_INLINE
RootParameters::RootParameters(HlslShaderMap const& shader_map)
{
	for (auto&& it : shader_map)
	{
		auto const& stage = it.first;
		auto const& shader = it.second;

		auto const& descriptor_ranges = shader->GetDescriptorRanges();

		if (!descriptor_ranges.empty())
		{
			::D3D12_ROOT_PARAMETER1 param;
			param.ParameterType    = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			param.ShaderVisibility = detail::ToShaderVisibility(stage);
			param.DescriptorTable.NumDescriptorRanges = static_cast<::UINT>(descriptor_ranges.size());
			param.DescriptorTable.pDescriptorRanges   = descriptor_ranges.data();
			m_root_parameters.push_back(param);
		}

		auto const& sampler_descriptor_ranges = shader->GetSamplerDescriptorRanges();

		if (!sampler_descriptor_ranges.empty())
		{
			::D3D12_ROOT_PARAMETER1 param;
			param.ParameterType    = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			param.ShaderVisibility = detail::ToShaderVisibility(stage);
			param.DescriptorTable.NumDescriptorRanges = static_cast<::UINT>(sampler_descriptor_ranges.size());
			param.DescriptorTable.pDescriptorRanges   = sampler_descriptor_ranges.data();
			m_root_parameters.push_back(param);
		}
	}
}

BKSGE_INLINE
RootParameters::~RootParameters()
{
}

BKSGE_INLINE ::UINT
RootParameters::GetSize(void) const
{
	return static_cast<::UINT>(m_root_parameters.size());
}

BKSGE_INLINE ::D3D12_ROOT_PARAMETER1 const*
RootParameters::GetData(void) const
{
	return m_root_parameters.data();
}

BKSGE_INLINE ::D3D12_ROOT_PARAMETER_TYPE
RootParameters::GetType(::UINT index) const
{
	return m_root_parameters[index].ParameterType;
}

BKSGE_INLINE ::D3D12_DESCRIPTOR_RANGE_TYPE
RootParameters::GetDescriptorRangeType(::UINT index) const
{
	return m_root_parameters[index].DescriptorTable.pDescriptorRanges[0].RangeType;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_ROOT_PARAMETERS_INL_HPP
