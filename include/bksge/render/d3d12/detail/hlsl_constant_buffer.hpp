/**
 *	@file	hlsl_constant_buffer.hpp
 *
 *	@brief	HlslConstantBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_HLSL_CONSTANT_BUFFER_HPP
#define BKSGE_RENDER_D3D12_DETAIL_HLSL_CONSTANT_BUFFER_HPP

#include <bksge/render/d3d12/detail/fwd/hlsl_constant_buffer_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/resource_cache_fwd.hpp>
#include <bksge/render/d3d12/detail/fwd/descriptor_heaps_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/d3d_common/d3d12shader.hpp>
#include <bksge/render/fwd/shader_parameter_map_fwd.hpp>
#include <string>
#include <vector>

namespace bksge
{

namespace render
{

namespace d3d12
{

class HlslConstantBuffer
{
public:
	explicit HlslConstantBuffer(
		::ID3D12ShaderReflectionConstantBuffer* constant_buffer);

	~HlslConstantBuffer();

	void UpdateParameters(
		DescriptorHeaps* descriptor_heaps,
		ResourceCache* resource_cache,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	struct Variable
	{
		std::string		m_name;
		::UINT			m_start_offset;
		::UINT			m_size;
	};

	std::string					m_name;
	::UINT						m_size = 0;
	std::vector<Variable>		m_variables;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/hlsl_constant_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_HLSL_CONSTANT_BUFFER_HPP
