/**
 *	@file	d3d11_shader_inl.hpp
 *
 *	@brief	D3D11Shader クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_SHADER_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_SHADER_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_shader.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11Shader::D3D11Shader(D3D11Renderer* renderer, Shader const& shader)
{
	(void)renderer;
	(void)shader;
}

BKSGE_INLINE
void D3D11Shader::Render(D3D11Renderer* renderer, Geometry const& geometry, Shader const& shader)
{
	(void)renderer;
	(void)geometry;
	(void)shader;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_SHADER_INL_HPP
