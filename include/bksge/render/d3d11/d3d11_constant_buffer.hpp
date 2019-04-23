/**
 *	@file	d3d11_constant_buffer.hpp
 *
 *	@brief	D3D11ConstantBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_CONSTANT_BUFFER_HPP
#define BKSGE_RENDER_D3D11_D3D11_CONSTANT_BUFFER_HPP

#include <bksge/render/d3d11/fwd/d3d11_constant_buffer_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_device_context_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/d3d_common/d3d11shader.hpp>
#include <bksge/render/d3d_common/com_ptr.hpp>
#include <bksge/render/detail/fwd/shader_parameter_map_fwd.hpp>
#include <string>
#include <vector>
#include <cstdint>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
class D3D11ConstantBuffer
{
public:
	D3D11ConstantBuffer(
		D3D11Device* device,
		::ID3D11ShaderReflectionConstantBuffer* constant_buffer);

	~D3D11ConstantBuffer();

	void LoadParameters(
		D3D11DeviceContext* device_context,
		ShaderParameterMap const& shader_parameter_map);

	ComPtr<::ID3D11Buffer> const& buffer(void) const;

private:
	struct Variable
	{
		std::string		m_name;
		::UINT			m_start_offset;
		::UINT			m_size;
	};

	std::string					m_name;
	::UINT						m_size;
	ComPtr<::ID3D11Buffer>		m_buffer;
	std::vector<std::uint8_t>	m_buffer_data;
	std::vector<Variable>		m_variables;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_constant_buffer_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_CONSTANT_BUFFER_HPP
