/**
 *	@file	d3d11_texture.hpp
 *
 *	@brief	D3D11Texture の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_TEXTURE_HPP
#define BKSGE_RENDER_D3D11_D3D11_TEXTURE_HPP

#include <bksge/render/d3d11/fwd/d3d11_texture_fwd.hpp>
#include <bksge/render/d3d11/fwd/d3d11_renderer_fwd.hpp>
#include <bksge/render/d3d11/d3d11.hpp>
#include <bksge/render/d3d_helper/com_ptr.hpp>
#include <bksge/render/fwd/texture_fwd.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	TextureをD3D11で使えるように変換したクラス
 */
class D3D11Texture
{
public:
	explicit D3D11Texture(D3D11Renderer* renderer, Texture const& texture);

	~D3D11Texture();

	::ID3D11Texture2D* texture() const;
	::ID3D11ShaderResourceView* shader_resource_view() const;

private:
	ComPtr<::ID3D11Texture2D>          m_texture;
	ComPtr<::ID3D11ShaderResourceView> m_shader_resource_view;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_texture_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_TEXTURE_HPP
