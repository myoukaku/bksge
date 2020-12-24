/**
 *	@file	hlsl_constant_buffer.hpp
 *
 *	@brief	HlslConstantBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_CONSTANT_BUFFER_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_CONSTANT_BUFFER_HPP

#include <bksge/core/render/d3d12/detail/fwd/hlsl_constant_buffer_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/resource_pool_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/descriptor_heaps_fwd.hpp>
#include <bksge/core/render/d3d12/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/d3d_common/d3d12shader.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/vector.hpp>

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
		Device* device,
		DescriptorHeaps* descriptor_heaps,
		ResourcePool* resource_pool,
		bksge::ShaderParameterMap const& shader_parameter_map);

private:
	// noncopyable
	HlslConstantBuffer(HlslConstantBuffer const&) = delete;
	HlslConstantBuffer& operator=(HlslConstantBuffer const&) = delete;

private:
	struct Variable
	{
		bksge::string	m_name;
		::UINT			m_start_offset;
		::UINT			m_size;
	};

	bksge::string				m_name;
	::UINT						m_size = 0;
	bksge::vector<Variable>		m_variables;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/hlsl_constant_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_HLSL_CONSTANT_BUFFER_HPP
