﻿/**
 *	@file	constant_buffer.hpp
 *
 *	@brief	ConstantBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_CONSTANT_BUFFER_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_CONSTANT_BUFFER_HPP

#include <bksge/core/render/d3d11/detail/fwd/constant_buffer_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_context_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/d3d11shader.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/shader_parameter_map_fwd.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class ConstantBuffer
{
public:
	explicit ConstantBuffer(
		Device* device,
		::ID3D11ShaderReflectionConstantBuffer* constant_buffer);

	~ConstantBuffer();

	void LoadParameters(
		DeviceContext* device_context,
		bksge::ShaderParameterMap const& shader_parameter_map);

	ComPtr<::ID3D11Buffer> const& buffer(void) const;

private:
	// noncopyable
	ConstantBuffer(ConstantBuffer const&) = delete;
	ConstantBuffer& operator=(ConstantBuffer const&) = delete;

private:
	struct Variable
	{
		bksge::string	m_name;
		::UINT			m_start_offset;
		::UINT			m_size;
	};

	bksge::string					m_name;
	::UINT							m_size;
	ComPtr<::ID3D11Buffer>			m_buffer;
	bksge::vector<bksge::uint8_t>	m_buffer_data;
	bksge::vector<Variable>			m_variables;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/constant_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_CONSTANT_BUFFER_HPP
