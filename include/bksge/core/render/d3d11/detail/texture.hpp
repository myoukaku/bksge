/**
 *	@file	texture.hpp
 *
 *	@brief	Texture の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_TEXTURE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_TEXTURE_HPP

#include <bksge/core/render/d3d11/detail/fwd/texture_fwd.hpp>
#include <bksge/core/render/d3d11/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/d3d_common/com_ptr.hpp>
#include <bksge/core/render/fwd/texture_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

/**
 *	@brief
 */
class Texture
{
public:
	explicit Texture(Device* device, bksge::Texture const& texture);

	~Texture();

//	::ID3D11Texture2D* texture() const;
	::ID3D11ShaderResourceView* shader_resource_view() const;

private:
	// noncopyable
	Texture(Texture const&) = delete;
	Texture& operator=(Texture const&) = delete;

private:
	ComPtr<ID3D11Texture2DN>			m_texture;
	ComPtr<ID3D11ShaderResourceViewN>	m_shader_resource_view;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/texture_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_TEXTURE_HPP
